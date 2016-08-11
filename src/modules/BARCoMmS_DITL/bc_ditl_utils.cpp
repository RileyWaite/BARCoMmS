#include "bc_ditl.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QScrollBar>

#include "bc_ditl_constants.cpp"

void BC_DITL::ditlError(QString err, QString det)
    // Add an error item to the event tree
{
    // Initializer bool
    static bool init = true;

    // List of errors
    static std::vector<QTreeWidgetItem*> errors, errorChildren;
    static unsigned short errN = 0; // Error count

    // Initialization routine
    if(init)
    {
        graph->Error->setFont(0, QFont("serif", 20));
        graph->Error->setTextColor(0, QColor(Qt::red));
        ui->severityTree->insertTopLevelItem(0, graph->Error);
        init = false;
    }

    // Add argument to error list
    errors.push_back(new QTreeWidgetItem(QStringList(err)));
    errorChildren.push_back(new QTreeWidgetItem(QStringList(det)));

    // Set the font
    errors.back()->setFont(0, QFont("serif", 15));
    errorChildren.back()->setFont(0, QFont("serif", 15));

    // Add error as a child to the Error toplevelitem
    errors.back()->addChild(errorChildren.back());
    graph->Error->addChild(errors.back());

    // Set Error text (update counter)
    graph->Error->setText(0,QString("ERRORS (").append(QString::number(++errN)).append(")"));

    // Expand routine to set newest error as focus
    for(unsigned short i(0); i<graph->Error->childCount(); ++i) graph->Error->child(i)->setExpanded(false);
    graph->Error->setExpanded(true);
    errors.back()->setExpanded(true);

    // Scroll tree to the error
    QModelIndex ind = ui->severityTree->model()->index(0, 0);
    ui->severityTree->scrollTo(ind);
}

QString BC_DITL::sevToQString(BC_Event::Severity type)
    // Returns the string equivalent of argued severity
{
    if(type == BC_Event::Severity::ADVISORY) return QString("Advisory");
    if(type == BC_Event::Severity::CAUTION) return QString("CAUTION");
    if(type == BC_Event::Severity::WARNING) return QString("WARNING");
    return QString("SEV_NOT_FOUND");
}

void BC_DITL::on_actionShowLegend_triggered() { legendWindow.show(); }

void BC_DITL::on_actionZoom_triggered()
{
    bool ok;
    double dt = QInputDialog::getDouble(this, tr("DITL: Set Timestamp increment"), tr("Time Increment (min)"), (double)graph->timeStep/60, 0.01, 2147483647, 2, &ok);
    uint64_t newTimeStep = (uint64_t)(dt*60);
    if(newTimeStep!=graph->timeStep && ok) repaint(newTimeStep);
    else ui->DITL_statusBar->showMessage(QString("Input timestep is indifferent from the current one. Nothing to do..."), 3000);
}

void BC_DITL::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit\nBARCoMmS Day in the Life?",
                                                              QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        // "Destructor"
        eventFile.close();
        emit dying();
        event->accept();
    }
    else event->ignore();
}

void BC_DITL::ditlLog(QString in) { ditlLog(in.toStdString()); }

void BC_DITL::ditlLog(std::string in)
{
    if(in.size()!=0)
    {
        std::ofstream log(DITL_LOG_FILE, ios_base::app);
        std::string ct = QTime::currentTime().toString().toStdString();
        log << '[' << ct << "] " << in << endl;
    }
}
