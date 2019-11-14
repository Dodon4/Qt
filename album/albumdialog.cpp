#include "albumdialog.h"
#include "ui_albumdialog.h"
#include<QFileDialog>
AlbumDialog::AlbumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlbumDialog)
{
    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    this->setWindowTitle("Альбом");
}

AlbumDialog::~AlbumDialog()
{
    delete ui;
}

void AlbumDialog::setModel(MusicModel *m)
{
    m_mapper.setModel(m);
}


void AlbumDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();
}

bool AlbumDialog::addAlbum(MusicModel *model, const QModelIndex &parent)
{
    setModel(model);
    int row = model->rowCount(parent);
    if(!model->insertRow(row, parent))
        return false;
    QModelIndex index = model->index(row, 0, parent);
    setModelIndex(index);
    if(!exec())
    {
        model->removeRow(row, parent);
        return false;
    }
    return true;
}

void AlbumDialog::on_pushButton_clicked()
{
   fileName = QFileDialog::getOpenFileName(this,tr(""), " ", tr("Image Files (*.png *.jpg *.bmp)"));
   QPixmap img;
   img.load(fileName);
   QPixmap iml=img.scaled(150,150);
   ui->label_5->setPixmap(iml);
}

void AlbumDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    Item *parIt = static_cast<Item*>(index.parent().internalPointer());
    ui->lineEdit->setText(parIt->name());
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setEnabled(false);
    m_mapper.addMapping(ui->lineEdit_2,0);
    m_mapper.addMapping(ui->plainTextEdit,1);
    m_mapper.addMapping(ui->spinBox,2);
    m_mapper.addMapping(ui->lineEdit_3,3);
    m_mapper.addMapping(ui->label_5,4);
    m_mapper.setCurrentIndex(index.row());
}
