#include "bc_bulletin.h"
#include "ui_bc_bulletin.h"

//Search function, slot searches tree items for user input and highlights all matches
void BC_Bulletin::goTo()
{
    //Store keyboard input in search bar as string, erase seach bar
    QString search = ui->searchBar->text();
    ui->searchBar->clear();

    //Deselect all items in CFDP tree
    QList<QTreeWidgetItem*> old = ui->tx->selectedItems();
    if(!old.empty())
    {
        for(int i = 0; i < old.size(); ++i) ui->tx->setItemSelected(old[i], false);
    }

    //Deselect all items in FSW tree
    QList<QTreeWidgetItem*> fswOld = ui->fsw->selectedItems();
    if(!fswOld.empty())
    {
        for(int i = 0; i < fswOld.size(); ++i) ui->fsw->setItemSelected(fswOld[i], false);
    }

    //Count is total items in tree, countCompare is total items that have been checked (increments throughout search so that progress can be tracked)
    unsigned int count(0), countCompare(0);

    //Flag if search returns a result
    bool found = 0;

    //Counts total items (including children and grandchildren) in CFDP tree
    for(unsigned int i(0); i < treeItems.size(); ++i)
    {
        ++count;
        for(unsigned int j(0); j < treeItems[i].children.size(); ++j)
        {
            ++count;
            for(unsigned int k(0); k < treeItems[i].children[j]->childCount(); ++k)
            {
                ++count;
            }
        }
    }

    //Counts total items (including children and grandchildren) in FSW tree
    for(unsigned int x(0); x < fswTreeItems.size(); ++x)
    {
        ++count;
        for(unsigned int y(0); y < fswTreeItems[x]->children.size(); ++y)
        {
            ++count;
            for(unsigned int z(0); z < treeItems[x].children[y]->childCount(); ++z)
            {
                ++count;
            }
        }
    }

    //Progress bar displays progress of search as percentage and slider
    ui->progressBar->setVisible(true);

    //Compares keyboard input to text in CFDP tree
    for(int i = 0; i < treeItems.size(); ++i)
    {
        //Searches top level items, selects item if match is found
        if(treeItems[i].topLevelItem->text(0).contains(search, Qt::CaseInsensitive) || treeItems[i].topLevelItem->text(1).contains(search, Qt::CaseInsensitive))
        {
            ui->tx->setItemSelected(treeItems[i].topLevelItem, true);
            found = 1;
        }
        //Update progress bar
        ++countCompare;
        ui->progressBar->setValue(((double)countCompare/count)*100);

        //Searches children, selects child and its top level item if match is found
        for(int j = 0; j < treeItems[i].children.size(); ++j)
        {
            if(treeItems[i].children[j]->text(0).contains(search, Qt::CaseInsensitive) || treeItems[i].children[j]->text(1).contains(search, Qt::CaseInsensitive))
            {
                ui->tx->setItemSelected(treeItems[i].children[j], true);
                ui->tx->setItemSelected(treeItems[i].topLevelItem, true);
                ui->tx->scrollToItem(treeItems[i].topLevelItem, QAbstractItemView::PositionAtTop);
                found = 1;
            }
            //Update progress bar
            ++countCompare;
            ui->progressBar->setValue(((double)countCompare/count)*100);

            //Searches grandchildren, selects grandchild, its parent, and its top level items if match is found
            for(int k = 0; k < treeItems[i].children[j]->childCount(); ++k)
            {
                if(treeItems[i].children[j]->child(k)->text(0).contains(search, Qt::CaseInsensitive) || treeItems[i].children[j]->child(k)->text(1).contains(search, Qt::CaseInsensitive))
                {
                    ui->tx->setItemSelected(treeItems[i].children[j]->child(k), true);
                    ui->tx->setItemSelected(treeItems[i].children[j], true);
                    ui->tx->setItemSelected(treeItems[i].topLevelItem, true);
                    ui->tx->scrollToItem(treeItems[i].topLevelItem, QAbstractItemView::PositionAtTop);
                    found = 1;
                }
                //Update progress bar
                ++countCompare;
                ui->progressBar->setValue(((double)countCompare/count)*100);
            }
        }
        QCoreApplication::processEvents();
    }

    //Compares keyboard input to text in FSW tree
    for(int x = 0; x < fswTreeItems.size(); ++x)
    {
        //Searches top level items, selects item if match is found
        if(fswTreeItems[x]->topLevelItem->text(0).contains(search, Qt::CaseInsensitive))
        {
            ui->fsw->setItemSelected(fswTreeItems[x]->topLevelItem, true);
            found = 1;
        }
        //Update progress bar
        ++countCompare;
        ui->progressBar->setValue(((double)countCompare/count)*100);

        //Searches children, selects child and its top level item if match is found
        for(int y = 0; y < fswTreeItems[x]->children.size(); ++y)
        {
            if(treeItems[x].children[y]->text(0).contains(search, Qt::CaseInsensitive))
            {
                ui->fsw->setItemSelected(fswTreeItems[x]->children[y], true);
                ui->fsw->setItemSelected(fswTreeItems[x]->topLevelItem, true);
                ui->fsw->scrollToItem(fswTreeItems[x]->topLevelItem, QAbstractItemView::PositionAtTop);
                found = 1;
            }
            //Update progress bar
            ++countCompare;
            ui->progressBar->setValue(((double)countCompare/count)*100);

            //Searches grandchildren, selects grandchild, its parent, and its top level item if match is found
            for(int z = 0; z < fswTreeItems[x]->children[y]->childCount(); ++z)
            {
                if(fswTreeItems[x]->children[y]->child(z)->text(0).contains(search, Qt::CaseInsensitive))
                {
                    ui->fsw->setItemSelected(fswTreeItems[x]->children[y]->child(z), true);
                    ui->fsw->setItemSelected(fswTreeItems[x]->children[y], true);
                    ui->fsw->setItemSelected(fswTreeItems[x]->topLevelItem, true);
                    ui->fsw->scrollToItem(fswTreeItems[x]->topLevelItem, QAbstractItemView::PositionAtTop);
                    found = 1;
                }
                //Update progress bar
                ++countCompare;
                ui->progressBar->setValue(((double)countCompare/count)*100);
            }
        }
        QCoreApplication::processEvents();
    }

    //Hide progress bar after search is complete
    ui->progressBar->setVisible(false);

    //Display message in search bar if no matches are found
    if(!found)
    {
        ui->searchBar->setText("No results found.");
        QTimer::singleShot(3000, this, SLOT(eraseSearchBar()));
        //dialog box instead?
    }
}

//Erase messages in search bar
void BC_Bulletin::eraseSearchBar()
{
    ui->searchBar->setText("");
}

//Toggle to expand/collapse item and its children
void BC_Bulletin::expandCollapseItem()
{
    QList<QTreeWidgetItem*> selection = ui->tx->selectedItems() + ui->fsw->selectedItems();

    for(int i = 0; i < selection.size(); ++i)
    {
        if(selection[i]->isExpanded())
        {
            selection[i]->setExpanded(false);
            for(int j = 0; j < selection[i]->childCount(); ++j) selection[i]->child(j)->setExpanded(false);
        }
        else
        {
            selection[i]->setExpanded(true);
            for(int j = 0; j < selection[i]->childCount(); ++j) selection[i]->child(j)->setExpanded(true);
        }
    }
}

//Toggle to expand/collapse all items
void BC_Bulletin::expandCollapseAll()
{
    bool expanded = 0;

    for(int i = 0; i < ui->tx->topLevelItemCount(); ++i)
    {
        if(ui->tx->topLevelItem(i)->isExpanded()) expanded = 1;
    }

    for(int x = 0; x < ui->fsw->topLevelItemCount(); ++x)
    {
        if(ui->fsw->topLevelItem(x)->isExpanded()) expanded = 1;
    }

    if(expanded == 1) {ui->tx->collapseAll(); ui->fsw->collapseAll();}
    else {ui->tx->expandAll(); ui->fsw->expandAll();}
}

//Toggle to automatically scroll to bottom when new item added
void BC_Bulletin::autoScroll()
{
    if (ui->pushButton_3->isChecked())
    {
        connect(this, SIGNAL(itemAdded()), ui->tx, SLOT(scrollToBottom()));
        connect(this, SIGNAL(itemAdded()), ui->fsw, SLOT(scrollToBottom()));
    }
    else
    {
        disconnect(this, SIGNAL(itemAdded()), ui->tx, SLOT(scrollToBottom()));
        disconnect(this, SIGNAL(itemAdded()), ui->fsw, SLOT(scrollToBottom()));
    }
}

//Toggle to automatically expand all items when new item added
void BC_Bulletin::autoExpand()
{
    if(ui->pushButton_4->isChecked())
    {
        connect(this, SIGNAL(itemAdded()), ui->tx, SLOT(expandAll()));
        connect(this, SIGNAL(itemAdded()), ui->fsw, SLOT(expandAll()));
    }
    else
    {
        disconnect(this, SIGNAL(itemAdded()), ui->tx, SLOT(expandAll()));
        disconnect(this, SIGNAL(itemAdded()), ui->fsw, SLOT(expandAll()));
    }
}

//Opens dialog box with options to sort tree items
void BC_Bulletin::openSorting()
{
    sorting->setModal(true);
    sorting->show();
}

//Sorts tree items according to user input
void BC_Bulletin::sortItems(int sortOption)
{
    //Sort tree items in chronoloical order (oldest first)
    if(sortOption == 0)
    {
        //Remove items from both trees
        removeItems(2);

        //Sort items in both trees by operator defined in Item.h and FSWItem.h, respectively
        std::sort(treeItems.begin(), treeItems.end(), sortByTimeCFDP());
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByTimeFSW());

        //Replace items in both trees
        replaceItems(2);
    }
    //Sort tree items in chronological order (newest first)
    else if(sortOption == 1)
    {
        removeItems(2);
        std::sort(treeItems.begin(), treeItems.end(), sortByTimeCFDP2());
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByTimeFSW2());
        replaceItems(2);
    }
    //Sort tree items by file size (CFDP only) (smallest first)
    else if(sortOption == 2)
    {
        removeItems(0);
        std::sort(treeItems.begin(), treeItems.end(), sortBySize());
        replaceItems(0);
    }
    //Sort tree items by file size (CFDP only) (largest first)
    else if(sortOption == 3)
    {
        removeItems(0);
        std::sort(treeItems.begin(), treeItems.end(), sortBySize2());
        replaceItems(0);
    }
    //Sort tree items by command (FSW only) (lowest APID first)
    else if(sortOption == 4)
    {
        removeItems(1);
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByCommand());
        replaceItems(1);
    }
    //Sort tree items by command (FSW only) (highest APID first)
    else if(sortOption == 5)
    {
        removeItems(1);
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByCommand2());
        replaceItems(1);
    }
    //Sort tree items by status (Successful, unsuccessful, in progress)
    else if(sortOption == 6)
    {
        removeItems(2);
        std::sort(treeItems.begin(), treeItems.end(), sortByStatusCFDP());
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByStatusFSW());
        replaceItems(2);
    }
    //Sort tree items by status (In progress, unsuccessful, successful)
    else if(sortOption == 7)
    {
        removeItems(2);
        std::sort(treeItems.begin(), treeItems.end(), sortByStatusCFDP2());
        std::sort(fswTreeItems.begin(), fswTreeItems.end(), sortByStatusFSW2());
        replaceItems(2);
    }
}

//Removes items from tree designated by user so sorting can take place
void BC_Bulletin::removeItems(int tree)
{
    bool both = 0;

    if(tree == 2) both = 1;

    if(tree == 0 | both)
    {
        for(int i = 0; i < treeItems.size(); ++i)
        {
            for(int j = 0; j < treeItems.size(); ++j)
            {
                ui->tx->takeTopLevelItem(j);
            }
        }
    }

    if(tree == 1 | both)
    {
        for(int x = 0; x < fswTreeItems.size(); ++x)
        {
            for(int y = 0; y < fswTreeItems.size(); ++y)
            {
                ui->fsw->takeTopLevelItem(y);
            }
        }
    }
}

//Replaces items from tree designated by user after sorting takes place
void BC_Bulletin::replaceItems(int tree)
{
    bool both = 0;
    if(tree == 2) both = 1;

    if(tree == 0 | both)
    {
        for(int k = 0; k < treeItems.size(); ++k)
        {
            ui->tx->addTopLevelItem(treeItems[k].topLevelItem);
        }
    }

    if(tree == 1 | both)
    {
        for(int z = 0; z < fswTreeItems.size(); ++z)
        {
            ui->fsw->addTopLevelItem(fswTreeItems[z]->topLevelItem);
        }
    }
}
