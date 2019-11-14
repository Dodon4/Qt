#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"musicmodel.h"
#include<QMessageBox>
#include<QFileDialog>
#include <QDebug>
#include"albumdialog.h"
#include"artistdialog.h"
#include"songdialog.h"
#include"ratingdelegate.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Моя музыка[*]");
    setCentralWidget(ui->treeView);
    model = new MusicModel();
    ui->treeView->setModel(model);
    ui->actionArtist->setEnabled(true);
    ui->actionAlbum->setEnabled(false);
    ui->actionSong->setEnabled(false);
    ui->actionChang->setEnabled(false);
    ui->actionDel->setEnabled(false);
    const int rc = 2;
    RatingDelegate *d = new RatingDelegate();
    ui->treeView->setItemDelegateForColumn(rc, d);
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(ConMenu(QPoint)));
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(documentModified()));
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(activeAction(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ConMenu(QPoint point)
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    Item *item=static_cast<Item*>(index.internalPointer());
    QPoint position = ui->treeView->mapToGlobal(point);
    QMenu contMenu;
    contMenu.addAction(ui->actionChang);
    if(item)
    {
        if(item->toArtist())
        {
            contMenu.addAction(ui->actionAlbum);;
            contMenu.exec(position);
        }
        if(item->toAlbum())
        {
            contMenu.addAction(ui->actionSong);
            contMenu.exec(position);
        }
        if(item->toSong())
            contMenu.exec(position);
    }

}

void MainWindow::documentModified()
{
    setWindowModified(true);
}

void MainWindow::activeAction(QModelIndex index)
{
    Item *item=static_cast<Item*>(index.internalPointer());
    if(item->toArtist())
    {
        ui->actionAlbum->setEnabled(true);
        ui->actionArtist->setEnabled(true);
        ui->actionDel->setEnabled(true);
        ui->actionChang->setEnabled(true);
        ui->actionSong->setEnabled(false);
    }
    if(item->toAlbum())
    {
        ui->actionAlbum->setEnabled(false);
        ui->actionArtist->setEnabled(true);
        ui->actionDel->setEnabled(true);
        ui->actionChang->setEnabled(true);
        ui->actionSong->setEnabled(true);
    }
    if(item->toSong())
    {
        ui->actionAlbum->setEnabled(false);
        ui->actionArtist->setEnabled(true);
        ui->actionDel->setEnabled(true);
        ui->actionChang->setEnabled(true);
        ui->actionSong->setEnabled(false);
    }
    if(!item)
    {
        ui->actionAlbum->setEnabled(false);
        ui->actionArtist->setEnabled(true);
        ui->actionDel->setEnabled(false);
        ui->actionChang->setEnabled(false);
        ui->actionSong->setEnabled(false);
    }
}

void MainWindow::loadFile(QString fileName)
{
    QFile new_file(fileName);
    if(!new_file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не может быть открыт"));
        return;
    }
    curFile=fileName;
    delete model->m_root;
    model->m_root = new Item();
    QDataStream stream(&new_file);
    stream >> *(model->m_root);
    setWindowTitle(QString("%1[*]").arg(curFile.isNull()?"NewFile.txt":QFileInfo(curFile).fileName()));
    new_file.close();
    ui->actionChang->setEnabled(false);
    ui->actionDel->setEnabled(false);
    ui->actionAlbum->setEnabled(false);
    ui->actionSong->setEnabled(false);
    ui->treeView->setModel(model);
    ui->treeView->reset();
}

bool MainWindow::savefileas()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), curFile.isNull()?QDir::currentPath():curFile, tr("Text files(*.txt)"));
    if(!fileName.isEmpty())
       {
           curFile=fileName;
           return saveFile();
       }
    return false;
}

bool MainWindow::saveFile()
{
  if(curFile.isNull())
    {
        return savefileas();
    }
  else
    {
        QFile new_file(curFile);
        if(!new_file.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, tr("Ошибка"), tr("Нельзя сохранить файл"));
            return false;
        }
        else
        {
            QDataStream stream(&new_file);
            stream << *(model->m_root);
            setWindowModified(false);
            setWindowTitle(QString("%1[*]").arg(curFile.isNull()?"NewFile.db":QFileInfo(curFile).fileName()));
            new_file.close();
            return true;
        }  
     }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr(""), " ", tr("Text (*.txt)"));
    if(fileName.isEmpty())
        return;
    if(!fileName.isEmpty()&!isWindowModified())
        loadFile(fileName);
    else
    {
        MainWindow *q=new MainWindow;
        q->show();
        q->loadFile(fileName);
    }
}

bool MainWindow::on_actionSave_triggered()
{
    if(curFile.isEmpty())
        return on_actionSaveAs_triggered();
    else
        return saveFile();
}

void MainWindow::on_actionClose_triggered()
{
   this->close();
}

void MainWindow::on_actionArtist_triggered()
{
    ArtistDialog *dialog = new ArtistDialog();
    if(dialog->addArtist(model, QModelIndex()))
        documentModified();
    else
       return;
}

void MainWindow::on_actionAlbum_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    AlbumDialog *album= new AlbumDialog();
    if(album->addAlbum(model, cur_index))
        documentModified();
    else
        return;
}

void MainWindow::on_actionSong_triggered()
{
    QModelIndex cur_index = ui->treeView->selectionModel()->currentIndex();
    SongDialog *s= new SongDialog();
    if(s->addSong(model, cur_index))
        documentModified();
    else
        return;
}
void MainWindow::on_actionChang_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    Item *item=static_cast<Item*>(index.internalPointer());
    if(item->toArtist())
    {
        ArtistDialog *ar = new ArtistDialog();
        ar->setModel(model);
        ar->setModelIndex(index);
        ar->show();
    }
    if(item->toAlbum())
    {
        AlbumDialog *al = new AlbumDialog();
        al->setModel(model);
        al->setModelIndex(index);
        al->show();
    }
    if(item->toSong())
    {
        SongDialog *s = new SongDialog();
        s->setModel(model);
        s->setModelIndex(index);
        s->show();
    }
}

void MainWindow::on_actionDel_triggered()
{
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
    model->removeRow(index.row(),index.parent());
    documentModified();
    activeAction(ui->treeView->selectionModel()->currentIndex());
}

bool MainWindow::on_actionSaveAs_triggered()
{
    return savefileas();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    if(this->isWindowModified())
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Документ изменен."));
        msgBox.setInformativeText(tr("Сохранить?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save, tr("Да"));
        msgBox.setButtonText(QMessageBox::Discard, tr("Нет"));
        msgBox.setButtonText(QMessageBox::Cancel, tr("Отмена"));
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowIcon(this->windowIcon());
        int ret = msgBox.exec();
        switch (ret)
        {
            case QMessageBox::Save:
            {
                if(saveFile())
                {
                    event->accept();
                }
                else
                {
                    event->ignore();
                }
                break;
            }
            case QMessageBox::Discard:
                event->accept();
                break;
            case QMessageBox::Cancel:
                event->ignore();
                break;
            default:
                break;
         }
    }
    else
      event->accept();
}
