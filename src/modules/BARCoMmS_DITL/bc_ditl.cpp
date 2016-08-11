#include "bc_ditl.h"

#include <QScrollBar>

#include "bc_ditl_constants.cpp"

BC_DITL::BC_DITL(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BC_DITL)
{
    // Start log file
    ditlLog(std::string("INITIALIZING"));

    // Set this class as the Ui parent
    ditlLog(std::string("Setting up Ui parent..."));
    ui->setupUi(this);

    // Set the window icon
    ditlLog(std::string("Setting window icon..."));
    setWindowIcon(QIcon(QString(RESOURCE_LOCATION).append("BC_Logo.PNG")));

    // Allocate graphics object
    ditlLog(std::string("Allocating graphics object..."));
    graph = new Graph;

    // Set scene parents
    ditlLog(std::string("Setting scene parents..."));
    graphScene = new QGraphicsScene(this);
    nameScene = new QGraphicsScene(this);
    timeScene = new QGraphicsScene(this);

    // Set graphics view scenes
    ditlLog(std::string("Setting graphicsview scenes..."));
    ui->DITL_graphicsView->setScene(graphScene);
    ui->DITL_graphicsView_LEFT->setScene(nameScene);
    ui->DITL_graphicsView_BOTT->setScene(timeScene);

    // Aligns scene with graphics view for relative geometry
    ditlLog(std::string("Alligning scene relative geometry..."));
    ui->DITL_graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->DITL_graphicsView_LEFT->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->DITL_graphicsView_BOTT->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Resize to make this frame the largest
    //  Needs to be done due to layout preference shrinking
    //  the central frame to its minimum width.
    ditlLog(std::string("Adjusting main graphicsview frame for initialization..."));
    ui->centralFrame->resize(950,ui->centralFrame->height());
    ui->DITL_graphicsView->updateGeometry();

    // QTreeWidget word wrap is limited to three lines, for some reason. Many headaches...
    ditlLog(std::string("Setting severity tree parameters..."));
    ui->severityTree->setWordWrap(true);

    // Add the top level items to the widget
    ditlLog(std::string("Populating top-level items in severity tree..."));
    ui->severityTree->addTopLevelItems(graph->topLevelList);

    // Set the arrow image
    ditlLog(std::string("Fetching unbounded arrow image resource file at " + QString(RESOURCE_LOCATION).append("ditl_Arrow.png").toStdString() + "..."));
    unboundedArrowRight = new QPixmap(QString(RESOURCE_LOCATION).append("ditl_Arrow.png"));

    // Set BC Logo in bottom left
    ditlLog(std::string("Fetching BARCoMmS logo image resource file at " + QString(RESOURCE_LOCATION).append("BC_Orange.PNG").toStdString() + "..."));
    QPixmap image(QString(RESOURCE_LOCATION).append("BC_Orange.PNG"));

    // Define geometries
    ditlLog(std::string("Fetching goemetric constants..."));
    eventHeight = EVENT_ITEM_HEIGHT; // TODO: Initializatino params (replace all the #defs)

    // Paint and align the BC logo
    ditlLog(std::string("Painting and aligning logo..."));
    ui->DITL_BCLOGO->setPixmap(image);
    ui->DITL_BCLOGO->setAlignment(Qt::AlignCenter);

    // Define highlighting object
    ditlLog(std::string("Allocating highlight geometry objects..."));
    hl = new QGraphicsRectItem;

    // Define pen color/size
    ditlLog(std::string("Initializing graphics pens..."));
    outlinePen = new QPen(QColor(42,42,42)); outlinePen->setWidth(2);
    highlighter = new QPen(QColor(102,255,140)); highlighter->setWidth(3);
    warningPen = new QPen(Qt::red); warningPen->setWidth(3);
    linePen = new QPen(QColor(20,20,25)); linePen->setWidth(1);

    // Define font typeface/size
    ditlLog(std::string("Initializing typefaces..."));
    eventFont = new QFont("Times New Roman", 20);
    timeFont = new QFont("Times New Roman", 15);

    // Connect status bar message to log output
    ditlLog(std::string("Connecting object signals to slots..."));
    connect(ui->DITL_statusBar, SIGNAL(messageChanged(QString)), this, SLOT(ditlLog(QString)));

    // Connect double-click event from the event tree to item click method
    connect(ui->severityTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemClicked(QTreeWidgetItem*,int)));

    // Synchronize scrollbars
    connect(ui->DITL_graphicsView_LEFT->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->DITL_graphicsView->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->DITL_graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->DITL_graphicsView_LEFT->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->DITL_graphicsView_BOTT->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->DITL_graphicsView->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->DITL_graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->DITL_graphicsView_BOTT->horizontalScrollBar(), SLOT(setValue(int)));

    // Match scrollbar ranges
    ditlLog(std::string("Snapping scrollbars..."));
    ui->DITL_graphicsView->horizontalScrollBar()->setRange(ui->DITL_graphicsView_BOTT->horizontalScrollBar()->minimum(),ui->DITL_graphicsView_BOTT->horizontalScrollBar()->maximum());
    ui->DITL_graphicsView->verticalScrollBar()->setRange(ui->DITL_graphicsView_LEFT->verticalScrollBar()->minimum(),ui->DITL_graphicsView_LEFT->verticalScrollBar()->maximum());

    // Assign default timestep
    ditlLog(std::string("Assigning default timestep..."));
    graph->timeStep = TIMESLOT_INCREMENT_SECONDS;

    // Load event database singleton (file name arg)
    ditlLog(std::string("Loading event reference database from ../../../resources/fsw/config_data/event.list..."));
    db.load("../../../resources/fsw/config_data/event.list");

    // Load color database (file name arg)
    ditlLog(std::string("Loading color reference database from " + std::string(RESOURCE_LOCATION).append("color.reference") + "..."));
    colorDB.load(std::string(RESOURCE_LOCATION).append("color.reference"));

    // Initialize the event name list (left list)
    ditlLog(std::string("Initializing event reference column..."));
    initEventNameList();

    // Open event file
    eventFile.open(EVENT_FILE, std::ios_base::app|std::ios_base::out|std::ios_base::in);

    ditlLog(std::string("FINISHED INITIALIZATION\n"));

    // Set status bar to "Waiting for Event PDUs..."
    ui->DITL_statusBar->showMessage("Waiting for Event PDUs...");

    // Temporary until real-time stuff
    addEvent(new BC_Event(100000250,1,3,static_cast<int>(BC_Event::EventType::END),static_cast<int>(BC_Event::Severity::ADVISORY),"1 END","/the/file/path/",46));
    addEvent(new BC_Event(100000300,2,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"2 POINT","/the/file/path/",46));
    addEvent(new BC_Event(100052050,1,1,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"1 POINT","/the/file/path/",46));

    addEvent(new BC_Event(100000300,3,3,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::WARNING),"3 START","/the/file/path/",46));
    addEvent(new BC_Event(100000600,3,3,static_cast<int>(BC_Event::EventType::END),static_cast<int>(BC_Event::Severity::WARNING),"3 END","/the/file/path/",46));

    addEvent(new BC_Event(100000600,4,4,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::CAUTION),"4 START","/the/file/path/",46));

    addEvent(new BC_Event(100231400,1,1,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::CAUTION),"THIS WAS ADDED","/the/file/path/",46));
    addEvent(new BC_Event(100251400,1,1,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"THIS WAS ADDED 2","/the/file/path/",46));
    addEvent(new BC_Event(100241400,2,2,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::WARNING),"THIS WAS ADDED START","/the/file/path/",54));
    addEvent(new BC_Event(100251400,2,2,static_cast<int>(BC_Event::EventType::END),static_cast<int>(BC_Event::Severity::WARNING),"THIS WAS ADDED END","/the/file/path/",54));
    addEvent(new BC_Event(100246400,3,3,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::CAUTION),"THIS WAS ADDED UNFINISHED","/the/file/path/",54));

    addEvent(new BC_Event(100000250,10,6,static_cast<int>(BC_Event::EventType::END),static_cast<int>(BC_Event::Severity::ADVISORY),"Panels are in sunlight","/src/power/panels.cpp/",54));
    addEvent(new BC_Event(100000550,10,6,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::ADVISORY),"Panels are in sunlight","/src/power/panels.cpp/",54));

    addEvent(new BC_Event(100000250,5,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"Panels were deployed","/src/power/panels.cpp/",79));

    addEvent(new BC_Event(100001850,6,3,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::ADVISORY),"Thruster is firing","/src/thruster/engage.cpp/",54));

    addEvent(new BC_Event(100000600,7,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"Taking picture","/src/cam/cam.cpp/",54));
    addEvent(new BC_Event(100001500,7,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::CAUTION),"Taking picture","/src/cam/cam.cpp/",54));
    addEvent(new BC_Event(100002400,7,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::WARNING),"Taking picture","/src/cam/cam.cpp/",54));
    addEvent(new BC_Event(100003300,7,2,static_cast<int>(BC_Event::EventType::POINT),static_cast<int>(BC_Event::Severity::ADVISORY),"Taking picture","/src/cam/cam.cpp/",54));

    addEvent(new BC_Event(100000250,8,6,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::WARNING),"Spinning reaction wheels","/src/power/wheels.cpp/",34));
    addEvent(new BC_Event(100000550,8,6,static_cast<int>(BC_Event::EventType::END),static_cast<int>(BC_Event::Severity::WARNING),"Spinning reaction wheels","/src/power/wheels.cpp/",154));

    addEvent(new BC_Event(100001650,11,6,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::WARNING),"Overcharged","/src/power/ppu.cpp/",27));

    addEvent(new BC_Event(100002600,12,7,static_cast<int>(BC_Event::EventType::START),static_cast<int>(BC_Event::Severity::ADVISORY),"Overcharged","/src/power/ppu.cpp/",27));
}

BC_DITL::~BC_DITL()
    // Destructor
{
    // "Actual" destructor is in bc_ditl_utils.cpp in overloaded closeEvent() if reply==yes condition
    delete ui;
}