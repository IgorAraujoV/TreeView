#include "treeapp.h"
#include "ui_treeapp.h"

TreeApp::TreeApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeApp)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Nome");
    ui->treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->treeWidget->setDragEnabled(true);
    ui->treeWidget->viewport()->setAcceptDrops(true);
    ui->treeWidget->setDropIndicatorShown(true);
    ui->treeWidget->setDragDropMode(QAbstractItemView::InternalMove);
    addTreeRoot();
}

TreeApp::~TreeApp()
{
    delete ui;
}

QTreeWidgetItem *TreeApp::addTreeRoot(){
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);

    treeItem->setText(0, "Default");

    return treeItem;
}

void TreeApp::addTreeChild(QTreeWidgetItem *parent){

    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable | Qt::ItemIsDragEnabled);

    treeItem->setText(0, "Default");
    parent->addChild(treeItem);
}

void TreeApp::on_btnAdd_clicked(){
    if(!ui->treeWidget->currentItem()->isSelected()){
        QTreeWidgetItem *root = addTreeRoot();
        root->setSelected(false);
    }

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if(item->isSelected()){
        addTreeChild(item);
        item->setSelected(false);
    }
}

void TreeApp::on_btnRemove_clicked()
{
    if(ui->treeWidget->currentItem()->isSelected()){
        delete ui->treeWidget->currentItem();
    }
}
