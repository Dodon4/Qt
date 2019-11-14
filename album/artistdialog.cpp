#include "artistdialog.h"
#include "ui_artistdialog.h"
#include<QFileDialog>
ArtistDialog::ArtistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistDialog)
{
    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    this->setWindowTitle("Исполнитель");
}

ArtistDialog::~ArtistDialog()
{
    delete ui;
}

void ArtistDialog::setModel(MusicModel *m)
{
    m_mapper.setModel(m);
}



void ArtistDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();
}

bool ArtistDialog::addArtist(MusicModel *model, const QModelIndex &parent)
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

void ArtistDialog::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this,tr(""), " ", tr("Image Files (*.png *.jpg *.bmp)"));
    QPixmap img;
    img.load(fileName);
    QPixmap iml=img.scaled(150,150);
    ui->label_3->setPixmap(iml);
}
void ArtistDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    m_mapper.addMapping(ui->lineEdit,0);
    m_mapper.addMapping(ui->lineEdit_2,1);
    m_mapper.addMapping(ui->plainTextEdit,2);
    m_mapper.addMapping(ui->label_3,3,"pixmap");
    m_mapper.setCurrentIndex(index.row());
}
