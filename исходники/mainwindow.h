#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mee.h"
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrinter>

class MainWindow : public QMainWindow, public mee
{
    Q_OBJECT
public:
    QPushButton *ckc, *cexamples, *form;
    QTableWidget *exp_obj, *exp_comp, *examples;
    QLineEdit *kc;
    QLabel *label1, *label2, *label3;
    QMenu  *mfile, *mhelp, *mnew, *mopen;
    QAction *anew, *anewform, *asave, *aopen, *aopenform, *aexit, *aprogram;
    void createWidgets();
    void createMenus();
    void createActions();
    void createConnections();
    void tableinmatrix();
    void newtable();
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotButton();
    void slotTable();
    void slotAction();
    void slotForm();
};

class FormDialog : public QDialog
{
    Q_OBJECT
public:
    QPushButton *save, *print, *cancel;
    QScrollArea *area;
    QGroupBox *group;
    QTextEdit *ICFP;
    QTextEdit *N, *N_pole, *NR, *NR_pole;
    QTextEdit *DN, *DN_pole, *DO, *DO_pole;
    QTextEdit *A, *A_pole;
    QTextEdit *KS, *KS_pole;
    QTextEdit *OF, *OF_pole;
    QTextEdit *SNR, *SNR_pole;
    QTextEdit *R, *R_pole;
    QTextEdit *I, *I_pole;
    QTextEdit *RIiR;
    QTextEdit *ma, *ma_pole, *prib, *prib_pole, *mat, *mat_pole;
    QTextEdit *t, *t_pole, *meh, *meh_pole, *ps, *ps_pole;
    QTextEdit *u, *u_pole, *prod, *prod_pole, *dru, *dru_pole;
    QTextEdit *O_pole;
    QTextEdit *NN, *NN_pole;
    QTextEdit *NIR, *NIR_pole;
    QTextEdit *NIOKR, *NIOKR_pole;
    QTextEdit *NA, *NA_pole;
    QTextEdit *PD;
    QTextEdit *P, *P_pole, *S, *S_pole;
    QTextEdit *L, *L_pole, *SV, *SV_pole;
    QTextEdit *Dr;
    void createConnections();
    void read(QString name);
    FormDialog( QWidget* parent = 0 );
    ~FormDialog();
public slots:
    void slotButton();
    void printDocument(QPrinter *printer_);
};

class FindDialog : public QDialog
{
    Q_OBJECT
public:
    QPushButton *open, *filtr, *cancel;
    QTextEdit *request;
    QListWidget *list;
    QComboBox *combo;
    void createConnections();
    FindDialog( QWidget* parent = 0 );
    ~FindDialog();
public slots:
    void slotButton();
    void slotCombo(int k);
};

#endif // MAINWINDOW_H
