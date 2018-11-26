#include "treeapp.h"
#include "ui_treeapp.h"

TreeApp::TreeApp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeApp)
{
    ui->setupUi(this);
    ui->treeWidget->setHeaderLabel("Nome");
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
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);

    treeItem->setText(0, "Default");
    parent->addChild(treeItem);
}

void TreeApp::addTreeChildEspecific(QTreeWidgetItem *parent, QTreeWidgetItem *clone){

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(*clone);
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);

    //treeItem->setText(0, "Default");
    parent->addChild(treeItem);
}

void TreeApp::change(QTreeWidgetItem &current, QTreeWidgetItem &sibling){
    int childCurrent = current.childCount();
    int childSibling = sibling.childCount();

    QTreeWidgetItem itemAux = current;
    QTreeWidgetItem *auxCurrent;
    QTreeWidgetItem *auxSibling;

    current = sibling;

    for(int i=0; i<childSibling; i++){
        sibling.child(i)->setText(0,"clone");
        auxSibling = sibling.child(i)->clone();
        addTreeChildEspecific(&current, auxSibling);
    }

    for(int i=0; i<childSibling; i++)
        sibling.takeChild(i);

    for(int i=0; i<childCurrent; i++){
        current.child(i)->setText(0,"clone");
        auxCurrent = current.child(i)->clone();
        addTreeChildEspecific(&sibling, auxCurrent);
    }

    for(int i=0; i<childCurrent; i++)
        current.takeChild(i);

    sibling = itemAux;
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

void TreeApp::on_btnUp_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    int row = ui->treeWidget->currentIndex().row();

    if (row-1 >= 0){
        ui->treeWidget->currentIndex().sibling(row-1, 0);
        ui->treeWidget->setCurrentIndex(ui->treeWidget->currentIndex().sibling(row-1, 0));
        QTreeWidgetItem *itemUp = ui->treeWidget->currentItem();
        change(*item, *itemUp);
    }

}
