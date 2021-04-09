#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    catalogThread = new QThread(this);
    catalog = new Catalog;
    catalog->moveToThread(catalogThread);

    itemModel = new ItemModel(ui->listView);
    itemModel->setCatalog(catalog);

    ui->listView->setResizeMode(QListView::Adjust);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setModel(itemModel);


    connect(catalogThread,  &QThread::finished,         catalog,    &QObject::deleteLater);
    connect(catalog,        &Catalog::ItemeAdded,       itemModel,  &ItemModel::addItem);
    connect(this,           &MainWindow::requestItems,  catalog,    &Catalog::generateItems);

//    tester = new QAbstractItemModelTester(itemModel, QAbstractItemModelTester::FailureReportingMode::Fatal, this);
    catalogThread->start();

    /*
     * BUG REPRO: Change the following line for flicker.
     * The first argument tells how many items to create.
     * The second argument is the time to Sleep in ms bewteen each item creation
     *
     * When the Sleep argument is 10 ms, it creates 100 items per second. This
     * causes a clear flicker on a Release build (as well as Debug build)
     *
     * The flicker mostly goes away when the Sleep argument is set to 100 (i.e.
     * 10 insertions /sec)
     *
     * This has been verified on a Macbook Pro macOS Big Sur 11.2.3
     *
     * Qt 5.15.2 (x86_64-little_endian-lp64 shared (dynamic) release build;
     * by Clang 10.0.0 (clang-1000.11.45.5) (Apple)) on "cocoa"
     * OS: macOS 10.16 [darwin version 20.3.0]
     * Architecture: x86_64; features: SSE2 SSE3 SSSE3 SSE4.1 SSE4.2 AVX AVX2
     */
    emit requestItems(1000, 10);
}

MainWindow::~MainWindow()
{
    catalog->canceled = true;
    catalogThread->quit();
    catalogThread->wait();
    delete catalogThread;

    delete ui;
}

