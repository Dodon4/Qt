#include "songdialog.h"
#include "ui_songdialog.h"

SongDialog::SongDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SongDialog)
{
    ui->setupUi(this);
    m_mapper.setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    this->setWindowTitle("Песня");
}

SongDialog::~SongDialog()
{
    delete ui;
}


void SongDialog::setModelIndex(const QModelIndex &index)
{
    QModelIndex parent = index.parent();
    m_mapper.setRootIndex(parent);
    m_mapper.setCurrentModelIndex(index);
    Item *parIt = static_cast<Item*>(index.parent().internalPointer());
    ui->lineEdit_2->setText(parIt->name());
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_2->setEnabled(false);
    Item *gparIt = static_cast<Item*>(index.parent().parent().internalPointer());
    ui->lineEdit->setText(gparIt->name());
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setEnabled(false);
    m_mapper.addMapping(ui->lineEdit_3,0);
    m_mapper.addMapping(ui->timeEdit,1);
    m_mapper.addMapping(ui->spinBox,2);
    m_mapper.addMapping(ui->plainTextEdit,3);
    m_mapper.setCurrentIndex(index.row());
}
void SongDialog::accept()
{
    m_mapper.submit();
    QDialog::accept();
}

bool SongDialog::addSong(MusicModel *model, const QModelIndex &parent)
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
void SongDialog::setModel(MusicModel *m)
{
    m_mapper.setModel(m);
}
