/* FILE: comm.c 
 * VERSION: 2.3k 2004_09_20
 * SPECS:  
 *   See 'cfdp_requires.h' ('pdu_output__...' routines),
 *   and 'pdu_input.h' ('pdu_input__...' routines).
 * ORIGINAL PROGRAMMER:  Tim Ray 301-286-0581
 */

#include "cfdp_code.h"

#define COMM_COMMENT_CHAR ';'
#define COMM_HOSTS_TABLE "../FSW_CFDP/CFDP/CODE/mib.nodes"
#define COMM_MAX_LINE_LENGTH 132


typedef enum { COMM_UNUSED_MIN, COMM_VIA_UDP, COMM_UNUSED_MAX } COMM_TYPE;

typedef struct
{
  char            ip_address [32];  /* e.g. "128.183.44.155" */
  int             port_number;
} UDP_PARAMETERS;

typedef struct
{
  COMM_TYPE       type;
  union
  {
    UDP_PARAMETERS  udp;
    /* add more comm types later... */
  } parameters;
} NODE_COMM;



static char                 m_hosts_table [80] = COMM_HOSTS_TABLE;
static boolean              m_is_input_initialized = NO;
static boolean              m_is_output_initialized = NO;



/* Convert an IP address and a port to a CFDP node */
const char *toNode (const char *IP, unsigned int port, char *retNode){
    FILE                 *fp;
    char                  line [COMM_MAX_LINE_LENGTH];
    char                  node [COMM_MAX_LINE_LENGTH];
    char                  p1 [64];
    char                  p2 [64];
    char                  p3 [64];
    /*------------------------------------------------------------*/

    /* There is no "nodes" file */
    if((fp = fopen (m_hosts_table, "r")) == NULL){
        msg__ ("<ERROR> Comm is unable to open '%s'.\n", m_hosts_table);
        exit(1);
    }

    /* Read the node's comm parameters from the "nodes" file */
    while(!feof(fp)){
        fgets(line, COMM_MAX_LINE_LENGTH, fp);
        if(line[0] != COMM_COMMENT_CHAR){
            memset(node, 0, sizeof(node));
            memset(p1, 0, sizeof(p1));
            memset(p2, 0, sizeof(p2));
            memset(p3, 0, sizeof(p3));
            sscanf(line, "%80s %64s %64s %64s", node, p1, p2, p3);

            /* It uses UDP; get IP-address and port number */
            if (!strcmp (p1, "udp")){
                if(!strcmp(p2, IP) && (atoi(p3) == port)){
                    break;
                }
            }
        }
    }

    /* End of "nodes" file reached. IP/port was not found */
    if(feof(fp)){
        msg__ ("<ERROR> IP/port '%s/%s' is not in the nodes file ('%s').\n", IP, port, m_hosts_table);
        exit(1);
    }

    fclose (fp);
    strcpy(retNode, node);
    return (retNode);
}



/*=r=************************************************************************/
NODE_COMM m__node_comm (ID node_id)
   {
     FILE                 *fp;
     char                  id_as_string [64];
     char                  line [COMM_MAX_LINE_LENGTH];
     static NODE_COMM      node_comm;
     char                  node [COMM_MAX_LINE_LENGTH];
     char                  p1 [64];
     char                  p2 [64];
     char                  p3 [64];
   /*------------------------------------------------------------*/
     node_comm.type = COMM_UNUSED_MIN;

     /* Read the node's comm parameters from the "nodes" file */
     if ((fp = fopen (m_hosts_table, "r")) == NULL)
       /* There is no "nodes" file */
       {
         msg__ ("<ERROR> Comm is unable to open '%s'.\n", m_hosts_table);
         return (node_comm);
       }

     strcpy (id_as_string, cfdp_id_as_string (node_id));
     while (!feof (fp))
       {
         fgets (line, COMM_MAX_LINE_LENGTH, fp);
         if (line[0] != COMM_COMMENT_CHAR)
           {
	     memset (node, 0, sizeof(node));
	     memset (p1, 0, sizeof(p1));
	     memset (p2, 0, sizeof(p2));
	     memset (p3, 0, sizeof(p3));
             sscanf (line, "%80s %64s %64s %64s", node, p1, p2, p3);

             if (!strcmp (node, id_as_string))
               /* Found the desired node */
               {
                 if (!strcmp (p1, "udp"))
                   /* It uses UDP; get IP-address and port number */
                   {
                     node_comm.type = COMM_VIA_UDP;
                     strcpy (node_comm.parameters.udp.ip_address, p2);
                     sscanf (p3, "%u", &node_comm.parameters.udp.port_number);
                   }
                 else
                   /* <NOT_SUPPORTED> Only UDP comm is supported */
                   {
                     msg__ ("<ERROR> Mib: Unsupported comm-type (%s).\n",
                            p1);
                     return (node_comm);
                   }
                 break;
               }
           }
         if (feof (fp))
           msg__ ("<ERROR> Node '%s' is not in the nodes file ('%s').\n",
                  id_as_string, m_hosts_table);
       }

     fclose (fp);
     return (node_comm);
   }



/*****************/
/*** PDU input ***/
/*****************/


/*=r=************************************************************************/
boolean pdu_input__init (ID local_entity_id)
   {
     NODE_COMM     node_comm;
     boolean       status;
   /*------------------------------------------------------------*/

     /* Look up the comm info for the specified CFDP entity */
     node_comm = m__node_comm (local_entity_id);

     if (m_is_input_initialized)
       status = 1;

     else if (node_comm.type == COMM_VIA_UDP)
       {
         status = udp__open (node_comm.parameters.udp.port_number);
         if (status)
           /* For UDP, both input and output share the same init */
           {
             m_is_input_initialized = YES;
             m_is_output_initialized = YES;
           }
       }

     else
       {
         msg__ ("<ERROR>  Unable to initialize my local comm port.\n"
                "(This 'comm' module only supports UDP comm)\n");
         status = 0;
       }
     return (status);
   }



/*=r=************************************************************************/
boolean pdu_input__connect (ID remote_entity_id)
   {
     NODE_COMM         node_comm;
   /*------------------------------------------------------------*/
     /* Look up the comm info for the specified entity-id */
     node_comm = m__node_comm (remote_entity_id);

     if (node_comm.type != COMM_VIA_UDP)
       {
         /* <NOT_SUPPORTED> Only UDP comm is supported */
         msg__ ("<ERROR>  Unable to initialize comm with CFDP node #%s.\n"
                "(This 'comm' module only supports UDP comm)\n",
                cfdp_id_as_string(remote_entity_id));
         return (0);
       }
     
     udp__choose_partner (node_comm.parameters.udp.ip_address,
                          node_comm.parameters.udp.port_number);
     return (1);
   }



/*=r=************************************************************************/
boolean pdu_input__poll (DATA *data_unit)
   {
     boolean      is_there;
     LINK_TYPE    link_type;
     int          timeout;
   /*------------------------------------------------------------*/
     timeout = 0;
     link_type__get (&link_type);
     if ((link_type == LINK_TWO_WAY) ||
         (link_type == LINK_INPUT_ONLY))
       is_there = udp__read_data_with_timeout (timeout, data_unit); 
     else
       /* Currently this is no input link */
       is_there = NO;
     return (is_there);
   }





/*****************/
/*** PDU output ***/
/*****************/



/*=r=************************************************************************/
static boolean m__init_output (ID local_entity_id)
   {
     NODE_COMM     node_comm;
     boolean       status;
   /*------------------------------------------------------------*/
     if (m_is_output_initialized)
       status = 1;

     else if (node_comm.type == COMM_VIA_UDP)
       {
         status = udp__open (node_comm.parameters.udp.port_number);
         if (status)
           /* For UDP, both input and output share the same init */
           {
             m_is_input_initialized = YES;
             m_is_output_initialized = YES;
           }
       }

     else
       {
         msg__ ("<ERROR>  Unable to initialize my local comm port.\n"
                "(This 'comm' module only supports UDP comm)\n");
         status = 0;
       }
     return (status);
   }



/*=r=************************************************************************/
static boolean m__connect_output (ID remote_entity_id)
   {
     NODE_COMM         node_comm;
   /*------------------------------------------------------------*/
     /* Determine the comm parameters for the specified entity */
     node_comm = m__node_comm (remote_entity_id);

     if (node_comm.type != COMM_VIA_UDP)
       {
         /* <NOT_SUPPORTED> Only UDP comm is supported */
         msg__ ("<ERROR>  Unable to initialize comm with CFDP node #%s.\n"
                "(This 'comm' module only supports UDP comm)\n",
                cfdp_id_as_string(remote_entity_id));
         return (0);
       }
     
     udp__choose_partner (node_comm.parameters.udp.ip_address,
                          node_comm.parameters.udp.port_number);
     return (1);
   }



/*=r=************************************************************************/
boolean pdu_output__open (ID my_id, ID partner_id)
{
  /*------------------------------------------------------------*/
  if (!m__init_output (my_id))
    return (0);
  return (m__connect_output (partner_id));
}



/*=r=************************************************************************/
boolean pdu_output__ready (PDU_TYPE pdu_type, TRANSACTION trans,
			   ID remote_entity_id)
   {
     LINK_TYPE        link_type;
     u_int_1          random_0_through_100;
   /*------------------------------------------------------------*/
     /* This version ignores the given remote-entity-id!!!
      * (i.e. this version assumes there is only one partner entity)
      */

     link_type__get (&link_type);
     if ((link_type == LINK_TWO_WAY) ||
         (link_type == LINK_OUTPUT_ONLY))
       {
         random_0_through_100 = rand () % 101;
         if (random_0_through_100 >=10)
           return (YES);
         else
           return (NO);
       }
     else
       /* The current link does not support data output */
       return (NO);
   }



/*=r=************************************************************************/
void pdu_output__send (TRANSACTION trans, ID remote_entity_id, DATA *data_unit)
   {
     DATA         copy_of_input_data;
     LINK_TYPE    link_type;
     DATA         output;
   /*------------------------------------------------------------*/
     /* This version ignores the given remote-entity-id!!!
      * (i.e. this version assumes there is only one partner entity)
      */

     copy_of_input_data = *data_unit;

     link_type__get (&link_type);
     if ((link_type == LINK_TWO_WAY) ||
         (link_type == LINK_OUTPUT_ONLY))
       {
         link_sim__give_pdu (copy_of_input_data);
         while (link_sim__get_pdu (&output))
           udp__write_data (output);
       }
   }



/*=r=*************************************************************************/
void comm__set_hosts_table (char *hosts_table_file)
{
  /*------------------------------------------------------------*/

  strcpy (m_hosts_table, hosts_table_file);
}



