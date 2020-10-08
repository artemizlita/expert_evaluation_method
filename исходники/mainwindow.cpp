#include "mainwindow.h"
#include "mee.h"
#include <Qt>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createWidgets();
    createMenus();
    createActions();
    createConnections();
    newtable();

    QString fName = "./kk94.txt";
        readMatrOutFile(fName);
        QString st;
        newtable();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < d; ++j) {
                st = QString().setNum(e_o[i][j], 'i');
                QTableWidgetItem *item;
                item = new QTableWidgetItem;
                item->setText(st);
                exp_obj->setItem(i, j, item);
                exp_obj->item(i, j)->setFont(QFont("Times", 14, QFont::Bold));
                exp_obj->item(i, j)->setTextAlignment(Qt::AlignCenter);
            }
        }
        for (int i = 0; i < d; ++i) {
            e_c[i] = round(e_c[i] * 100) / 100;
            st = QString().setNum(e_c[i], 'f', 2);
            QTableWidgetItem *item, *item1;
            item = new QTableWidgetItem;
            item->setText(st);
            exp_comp->setItem(0, i, item);
            exp_comp->item(0, i)->setTextAlignment(Qt::AlignCenter);
            exp_comp->item(0, i)->setFont(QFont("Times", 18, QFont::Bold));
            st = QString().setNum(e_d[i], 'f', 2);
            item1 = new QTableWidgetItem;
            item1->setText(st);
            exp_comp->setItem(1, i, item1);
            exp_comp->item(1, i)->setTextAlignment(Qt::AlignCenter);
            exp_comp->item(1, i)->setFont(QFont("Times", 18, QFont::Bold));
        }
}

void MainWindow::createWidgets () {
    setFixedSize(1090, 715);
    label1 = new QLabel(this);
    label2 = new QLabel(this);
    label3 = new QLabel(this);
    exp_obj = new QTableWidget(m, d, this);
    exp_comp = new QTableWidget(2, d, this);
    ckc = new QPushButton("Рассчитать коэффициент конкордации", this);
    cexamples = new QPushButton("Вывести рейтинг проектов", this);
    cexamples->setDisabled(1);
    kc = new QLineEdit(this);
    kc->setReadOnly(1);
    kc->setStyleSheet("font-size: 50px");
    examples = new QTableWidget(m, 2, this);
    examples->setEditTriggers(QAbstractItemView::EditTriggers(0));
    form = new QPushButton("заполнить форму", this);
    form->setVisible(0);
}

void MainWindow::createMenus() {
    menuBar()->setFont(QFont("TimesNewRoman", 10, 1, true));
    mfile = new QMenu("&Файл", this);
    menuBar()->addMenu(mfile);
    mnew = new QMenu("&Создать", this);
    mopen = new QMenu("&Открыть", this);
    mhelp = new QMenu("&Справка", this);
    menuBar()->addMenu(mhelp);
}

void MainWindow::createActions() {
    anew = new QAction("&Проект", 0);
    anewform = new QAction("&Форму", 0);
    aopen = new QAction("&Проект", 0);
    aopenform = new QAction("&Форму", 0);
    asave = new QAction("&Сохранить проект", 0);
    aexit = new QAction("&Выход из программы", 0);
    aprogram = new QAction("&О программе", 0);
    mfile->addMenu(mnew);
    mnew->addAction(anew);
    mnew->addAction(anewform);
    mfile->addMenu(mopen);
    mopen->addAction(aopen);
    mopen->addAction(aopenform);
    mfile->addAction(asave);
    mfile->addAction(aexit);
    mhelp->addAction(aprogram);
}

void MainWindow::createConnections () {
    connect(ckc, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(cexamples, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(exp_obj, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(slotTable()));
    connect(exp_comp, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(slotTable()));
    connect(anew, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(anewform, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(aopen, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(aopenform, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(asave, SIGNAL(triggered()), this, SLOT(slotAction()));
    connect(aexit, SIGNAL(triggered()), this, SLOT(close()));
    connect(aprogram, SIGNAL(triggered()), this, SLOT(slotAction()));
}

void MainWindow::tableinmatrix() {
    QString r;
    e_o.clear();
    e_o.resize(m);
    for(int i = 0; i < m; ++i) {
        e_o[i].resize(d);
        for(int j = 0; j < d; ++j) {
            r = exp_obj->item(i, j)->text();
            e_o[i][j] = r.toInt();
        }
    }
    e_c.clear();
    e_c.resize(d);
    e_d.clear();
    e_d.resize(d);
    for(int i = 0; i < d; ++i) {
        r = exp_comp->item(0, i)->text();
        e_c[i] = r.toFloat();
        e_c[i] = (e_c[i] * 100) / 100;
        r = exp_comp->item(1, i)->text();
        e_d[i] = r.toFloat();
    }
}

void MainWindow::newtable() {
    exp_obj->clear();
    exp_comp->clear();
    examples->clear();
    kc->clear();
    exp_obj->setColumnCount(d);
    exp_obj->setRowCount(m);
    exp_comp->setColumnCount(d);
    examples->setRowCount(m);
    QStringList l, empty;
    QString empt = "";
    for (int i = 0; i < m; ++i) {
        QString st = "Проект " + QString().setNum(i + 1);
        l<<st;
        empty<<"                ";
        for (int j = 0; j < d; ++j) {
            QTableWidgetItem *item;
            item = new QTableWidgetItem;
            item->setText(empt);
            exp_obj->setItem(i, j, item);
            exp_obj->item(i, j)->setFont(QFont("Times", 14, QFont::Bold));
            exp_obj->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    exp_obj->setVerticalHeaderLabels(l);
    exp_comp->setVerticalHeaderLabels(QStringList() <<"Коэффициенты\nкомпетентности\nэкспертов"<<"Коэффициенты\nдостоверности\nэкспертов");
    examples->setVerticalHeaderLabels(empty);
    examples->setHorizontalHeaderLabels(QStringList() <<"Рейтинг"<<"Комментарий"<<"Форма");
    examples->setColumnWidth(0, 60);
    examples->setColumnWidth(1, 110);
    l.clear();
    for (int i = 0; i < d; ++i) {
        QString st = "Эксперт " + QString().setNum(i + 1);
        l<<st;
        exp_obj->setColumnWidth(i, 70);
        exp_comp->setColumnWidth(i, 70);
        QTableWidgetItem *item, *item1;
        item = new QTableWidgetItem;
        item->setText(empt);
        exp_comp->setItem(0, i, item);
        exp_comp->item(0, i)->setTextAlignment(Qt::AlignCenter);
        exp_comp->item(0, i)->setFont(QFont("Times", 18, QFont::Bold));
        item1 = new QTableWidgetItem;
        item1->setText(empt);
        exp_comp->setItem(1, i, item1);
        exp_comp->item(1, i)->setTextAlignment(Qt::AlignCenter);
        exp_comp->item(1, i)->setFont(QFont("Times", 18, QFont::Bold));
    }
    exp_comp->setRowHeight(0, 50);
    exp_comp->setRowHeight(1, 50);
    exp_obj->setHorizontalHeaderLabels(l);
    exp_comp->setHorizontalHeaderLabels(l);
    setFixedSize(545 + d * 70, 680);
    label1->setGeometry(25, 25, 120 + d * 70, 51);
    label1->setStyleSheet("font-size: 20px; border: 1px solid black");
    label1->setAlignment(Qt::AlignCenter);
    label1->setText("Матрица оценок");
    exp_obj->setGeometry(25, 75, 120 + d * 70, 430);
    exp_comp->setGeometry(25, 530, 120 + d * 70, 125);
    label2->setGeometry(170 + d * 70, 25, 350, 51);
    label2->setStyleSheet("font-size: 20px; border: 1px solid black");
    label2->setAlignment(Qt::AlignCenter);
    label2->setText("Коэффициент конкордации");
    kc->setGeometry(170 + d * 70, 75, 350, 70);
    ckc->setGeometry(170 + d * 70, 170, 350, 50);
    label3->setGeometry(170 + d * 70, 245, 232, 51);
    label3->setStyleSheet("font-size: 20px; border: 1px solid black");
    label3->setAlignment(Qt::AlignCenter);
    label3->setText("Рейтинг проектов");
    examples->setGeometry(170 + d * 70, 295, 232, 210);
    cexamples->setGeometry(170 + d * 70, 530, 350, 50);
}

void MainWindow::slotButton() {
    form->setVisible(0);
    if (sender() == ckc) {
        kc->clear();
        bool count = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < d; ++j) {
                bool ok;
                int mark = exp_obj->item(i, j)->text().toInt(&ok);
                if (ok) {
                    if (mark < 0 || mark > 5) {
                        count = 0;
                    }
                } else {
                    count = 0;
                }
            }
        }
        for (int i = 0; i < d; ++i) {
            bool ok;
            double c = exp_comp->item(0, i)->text().toDouble(&ok);
            if (ok) {
                if (c < 0 || c > 1) {
                    count = 0;
                }
            } else {
                count = 0;
            }
            double d = exp_comp->item(1, i)->text().toDouble(&ok);
            if (ok) {
                if (d <= 0 || d >= 1) {
                    count = 0;
                }
            } else {
                count = 0;
            }
        }
        if (count) {
            examples->clear();
            examples->setHorizontalHeaderLabels(QStringList() <<"Рейтинг"<<"Комментарий"<<"Форма");
            QStringList empty;
            for (int i = 0; i < m; ++i) {
                empty<<"                ";
            }
            examples->setVerticalHeaderLabels(empty);
            tableinmatrix();
            QString st;
            st = QString().setNum(find_kc(), 'f', 3);
            kc->setText(st);
            kc->setAlignment(Qt::AlignCenter);
            cexamples->setEnabled(1);
        } else {
            QMessageBox::critical(NULL,QObject::tr("Неправильно введены данные"),tr("Матрица оценок заполняется целыми числами от 0 до 5\nКоэффициенты компетентности и достоверности - это вещественные числа от 0 до 1"));
        }
    }
    if (sender() == cexamples) {
        vector<float> sr, sumc;
        vector<int> srk;
        sr.resize(m);
        srk.resize(m);
        sumc.resize(m);
        float c1 = e_c[0], c2 = e_c[1], c3 = e_c[2];
        float d1 = e_d[0], d2 = e_d[1], d3 = e_d[2];
        int k1 = 0, k2 = 1, k3 = 2;
        for (int j = 0; j < d; ++j) {
            if (e_c[j] > c3 && k1 != j && k2 != j && k3 != j) {
                c3 = e_c[j];
                k3 = j;
                d3 = e_d[j];
            }
            if (c3 > c2) {
                swap(c2, c3);
                swap(d2, d3);
                swap(k2, k3);
            }
            if (c2 > c1) {
                swap(c2, c1);
                swap(d2, d1);
                swap(k2, k1);
            }
        }
        for (int j = 0; j < d; ++j) {
            if (k1 != j && k2 != j && k3 !=j) {
                if (e_d[j] > d3 && e_c[j] == c3) {
                    c3 = e_c[j];
                    k3 = j;
                    d3 = e_d[j];
                }
            }
            if (d3 > d2 && c3 == c2) {
                swap(c2, c3);
                swap(d2, d3);
                swap(k2, k3);
            }
            if (d2 > d1 && c2 == c1) {
                swap(c2, c1);
                swap(d2, d1);
                swap(k2, k1);
            }
        }
        for (int i = 0; i < m; ++i) {
            sumc[i] = e_o[i][k1] + e_o[i][k2] + e_o[i][k3];
        }
        for (int i = 0; i < m; ++i) {
            sr[i] = 0;
            for (int j = 0; j < d; ++j) {
                sr[i] += e_o[i][j];
            }
            sr[i] /= d;
            srk[i] = i + 1;
        }
        for (int i = 0; i < m - 1; ++i) {
            float max = sr[0], maxc = sumc[0];
            int maxk = srk[0], t = 0;
            for (int j = 0; j < m - i; ++j) {
                if (sr[j] > max) {
                    max = sr[j];
                    maxk = srk[j];
                    maxc = sumc[j];
                    t = j;
                }
            }
            swap(sr[t], sr[m - i - 1]);
            swap(srk[t], srk[m - i - 1]);
            swap(sumc[t], sumc[m - i - 1]);
        }
        QStringList p;
        for (int i = 0; i < m; ++i) {
            QString stp = "Проект " + QString().setNum(srk[m - i - 1]);
            p<<stp;
        }
        int opt = m - 1;
        for (int i = 0; i < m - 1; ++i) {
            if (sr[i] + 0.15 >= sr[m - 1] && sumc[i] - 1 >= sumc[m - 1] && sumc[i] > sumc[opt]) {
                opt = i;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (sr[i] + 0.15 >= sr[m - 1] && e_o[srk[i] - 1][k1] > e_o[srk[opt] - 1][k1] && sumc[opt] == sumc[i]) {
                opt = i;
            }
        }
        QString st = "рекомендуется";
        QTableWidgetItem *item1;
        item1 = new QTableWidgetItem;
        item1->setText(st);
        examples->setItem(m - opt - 1, 1, item1);
        examples->item(m - opt - 1, 1)->setFont(QFont("Times", 10, QFont::Bold));
        examples->item(m - opt - 1, 1)->setTextAlignment(Qt::AlignCenter);
        form->setGeometry(400 + d * 70, 317 + 30 * (m - opt - 1), 120, 33);
        form->setVisible(1);
        connect(form, SIGNAL(clicked()), this, SLOT(slotForm()));
        examples->setVerticalHeaderLabels(p);
        for (int i = 0; i < m; ++i) {
            QString st = QString().setNum(sr[i], 'f', 2);
            QTableWidgetItem *item;
            item = new QTableWidgetItem;
            item->setText(st);
            examples->setItem(m - i - 1, 0, item);
            examples->item(m - i - 1, 0)->setFont(QFont("Times", 14, QFont::Bold));
            examples->item(m - i - 1, 0)->setTextAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::slotTable() {
    if (sender() == exp_obj) {
        cexamples->setDisabled(1);
    }
    if (sender() == exp_comp) {
        cexamples->setDisabled(1);
    }
}

void MainWindow::slotAction() {
    form->setVisible(0);
    if (sender() == anew) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("eem"), tr("Введите число объектов:"), QLineEdit::Normal,
                                                "", &ok);
        if (ok && !text.isEmpty()) m = text.toInt();
        text = QInputDialog::getText(this, tr("eem"), tr("Введите число экспертов:"), QLineEdit::Normal,
                                                "", &ok);
        if (ok && !text.isEmpty()) d = text.toInt();
        newtable();
    }
    if (sender() == anewform) {
        FormDialog d;
        d.setWindowTitle("Form");
        d.exec();
    }
    if (sender() == aopen) {
        QString fName = QFileDialog::getOpenFileName(this, tr("Open File"), "./", tr("matr(*.txt)"));
        if (fName != "") {
            QString suf = QFileInfo(fName).suffix();
            if (suf.isEmpty()) fName.append(".txt");
            readMatrOutFile(fName);
            QString st;
            newtable();
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < d; ++j) {
                    st = QString().setNum(e_o[i][j], 'i');
                    QTableWidgetItem *item;
                    item = new QTableWidgetItem;
                    item->setText(st);
                    exp_obj->setItem(i, j, item);
                    exp_obj->item(i, j)->setFont(QFont("Times", 14, QFont::Bold));
                    exp_obj->item(i, j)->setTextAlignment(Qt::AlignCenter);
                }
            }
            for (int i = 0; i < d; ++i) {
                e_c[i] = round(e_c[i] * 100) / 100;
                st = QString().setNum(e_c[i], 'f', 2);
                QTableWidgetItem *item, *item1;
                item = new QTableWidgetItem;
                item->setText(st);
                exp_comp->setItem(0, i, item);
                exp_comp->item(0, i)->setTextAlignment(Qt::AlignCenter);
                exp_comp->item(0, i)->setFont(QFont("Times", 18, QFont::Bold));
                st = QString().setNum(e_d[i], 'f', 2);
                item1 = new QTableWidgetItem;
                item1->setText(st);
                exp_comp->setItem(1, i, item1);
                exp_comp->item(1, i)->setTextAlignment(Qt::AlignCenter);
                exp_comp->item(1, i)->setFont(QFont("Times", 18, QFont::Bold));
            }
        }
    }
    if (sender() == aopenform) {
        FindDialog f;
        f.setWindowTitle("Find Form");
        f.exec();
    }
    if (sender() == asave) {
        tableinmatrix();
        QString fName = QFileDialog::getSaveFileName(this, tr("Save File"), "./", tr("matr(*.txt)"));
        QString suf = QFileInfo(fName).suffix();
        if (suf.isEmpty()) fName.append(".txt");
        writeMatrInFile(fName);
    }
    if (sender() == aprogram) {

    }
}

void MainWindow::slotForm() {
    if (sender() == form) {
        FormDialog d;
        d.setWindowTitle("Form");
        d.exec();
    }
}

MainWindow::~MainWindow()
{

}

FormDialog::FormDialog(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(840, 700);
    save = new QPushButton ("Сохранить", this);
    print = new QPushButton ("Печать", this);
    cancel = new QPushButton ("Отмена", this);
    save->setGeometry(25, 650, 100, 25);
    print->setGeometry(150, 650, 100, 25);
    cancel->setGeometry(275, 650, 100, 25);

    area = new QScrollArea(this);
    area->setGeometry(25, 25, 790, 600);
    group = new QGroupBox();
    group->setGeometry(0, 0, 760, 1090);
    area->setWidget(group);

    ICFP = new QTextEdit(group);
    ICFP->setGeometry(0, 0, 760, 40);
    ICFP->setText("Информационная карта форсайт-проекта");
    ICFP->setAlignment(Qt::AlignCenter);
    ICFP->setFont(QFont("Times", 18, QFont::Bold));
    ICFP->setReadOnly(1);
    N = new QTextEdit(group);
    N->setGeometry(0, 40, 120, 50);
    N->setText("Название");
    N->setFont(QFont("Times", 9, QFont::Bold));
    N->setReadOnly(1);
    N_pole = new QTextEdit(group);
    N_pole->setGeometry(120, 40, 280, 50);
    NR = new QTextEdit(group);
    NR->setGeometry(400, 40, 100, 50);
    NR->setText("Номер регистрации");
    NR->setFont(QFont("Times", 9, QFont::Bold));
    NR->setReadOnly(1);
    NR_pole = new QTextEdit(group);
    NR_pole->setGeometry(500, 40, 260, 50);

    DN = new QTextEdit(group);
    DN->setGeometry(0, 90, 120, 50);
    DN->setText("Дата начала");
    DN->setFont(QFont("Times", 9, QFont::Bold));
    DN->setReadOnly(1);
    DN_pole = new QTextEdit(group);
    DN_pole->setGeometry(120, 90, 280, 50);
    DO = new QTextEdit(group);
    DO->setGeometry(400, 90, 100, 50);
    DO->setText("Дата окончания");
    DO->setFont(QFont("Times", 9, QFont::Bold));
    DO->setReadOnly(1);
    DO_pole = new QTextEdit(group);
    DO_pole->setGeometry(500, 90, 260, 50);

    A = new QTextEdit(group);
    A->setGeometry(0, 140, 120, 100);
    A->setText("Аннотация");
    A->setFont(QFont("Times", 9, QFont::Bold));
    A->setReadOnly(1);
    A_pole = new QTextEdit(group);
    A_pole->setGeometry(120, 140, 640, 100);

    KS = new QTextEdit(group);
    KS->setGeometry(0, 240, 120, 50);
    KS->setText("Ключевые слова");
    KS->setFont(QFont("Times", 9, QFont::Bold));
    KS->setReadOnly(1);
    KS_pole = new QTextEdit(group);
    KS_pole->setGeometry(120, 240, 640, 50);

    OF = new QTextEdit(group);
    OF->setGeometry(0, 290, 120, 25);
    OF->setText("Финансирование");
    OF->setFont(QFont("Times", 9, QFont::Bold));
    OF->setReadOnly(1);
    OF_pole = new QTextEdit(group);
    OF_pole->setGeometry(120, 290, 640, 25);

    SNR = new QTextEdit(group);
    SNR->setGeometry(0, 315, 120, 100);
    SNR->setText("Сфера научных разработок");
    SNR->setFont(QFont("Times", 9, QFont::Bold));
    SNR->setReadOnly(1);
    SNR_pole = new QTextEdit(group);
    SNR_pole->setGeometry(120, 315, 640, 100);

    R = new QTextEdit(group);
    R->setGeometry(0, 415, 120, 25);
    R->setText("Руководитель");
    R->setFont(QFont("Times", 9, QFont::Bold));
    R->setReadOnly(1);
    R_pole = new QTextEdit(group);
    R_pole->setGeometry(120, 415, 640, 25);

    I = new QTextEdit(group);
    I->setGeometry(0, 440, 120, 125);
    I->setText("Исполнители");
    I->setFont(QFont("Times", 9, QFont::Bold));
    I->setReadOnly(1);
    I_pole = new QTextEdit(group);
    I_pole->setGeometry(120, 440, 640, 125);

    RIiR = new QTextEdit(group);
    RIiR->setGeometry(0, 565, 120, 175);
    RIiR->setText("Результат исследований и разработок\n\n\n\n\n\n\n\nОписание");
    RIiR->setFont(QFont("Times", 9, QFont::Bold));
    RIiR->setReadOnly(1);

    ma = new QTextEdit(group);
    ma->setGeometry(120, 565, 80, 50);
    ma->setText("методика, алгоритм");
    ma->setFont(QFont("Times", 9, QFont::Bold));
    ma->setReadOnly(1);
    ma_pole = new QTextEdit(group);
    ma_pole->setGeometry(200, 565, 120, 50);
    prib = new QTextEdit(group);
    prib->setGeometry(320, 565, 70, 50);
    prib->setText("прибор");
    prib->setFont(QFont("Times", 9, QFont::Bold));
    prib->setReadOnly(1);
    prib_pole = new QTextEdit(group);
    prib_pole->setGeometry(390, 565, 150, 50);
    mat = new QTextEdit(group);
    mat->setGeometry(540, 565, 100, 50);
    mat->setText("материал");
    mat->setFont(QFont("Times", 9, QFont::Bold));
    mat->setReadOnly(1);
    mat_pole = new QTextEdit(group);
    mat_pole->setGeometry(640, 565, 120, 50);

    t = new QTextEdit(group);
    t->setGeometry(120, 615, 80, 50);
    t->setText("технология");
    t->setFont(QFont("Times", 9, QFont::Bold));
    t->setReadOnly(1);
    t_pole = new QTextEdit(group);
    t_pole->setGeometry(200, 615, 120, 50);
    meh = new QTextEdit(group);
    meh->setGeometry(320, 615, 70, 50);
    meh->setText("механизм");
    meh->setFont(QFont("Times", 9, QFont::Bold));
    meh->setReadOnly(1);
    meh_pole = new QTextEdit(group);
    meh_pole->setGeometry(390, 615, 150, 50);
    ps = new QTextEdit(group);
    ps->setGeometry(540, 615, 100, 50);
    ps->setText("программное средство");
    ps->setFont(QFont("Times", 9, QFont::Bold));
    ps->setReadOnly(1);
    ps_pole = new QTextEdit(group);
    ps_pole->setGeometry(640, 615, 120, 50);

    u = new QTextEdit(group);
    u->setGeometry(120, 665, 80, 50);
    u->setText("устройство");
    u->setFont(QFont("Times", 9, QFont::Bold));
    u->setReadOnly(1);
    u_pole = new QTextEdit(group);
    u_pole->setGeometry(200, 665, 120, 50);
    prod = new QTextEdit(group);
    prod->setGeometry(320, 665, 70, 50);
    prod->setText("продукт");
    prod->setFont(QFont("Times", 9, QFont::Bold));
    prod->setReadOnly(1);
    prod_pole = new QTextEdit(group);
    prod_pole->setGeometry(390, 665, 150, 50);
    dru = new QTextEdit(group);
    dru->setGeometry(540, 665, 100, 50);
    dru->setText("другое (укажите)");
    dru->setFont(QFont("Times", 9, QFont::Bold));
    dru->setReadOnly(1);
    dru_pole = new QTextEdit(group);
    dru_pole->setGeometry(640, 665, 120, 50);

    O_pole = new QTextEdit(group);
    O_pole->setGeometry(120, 715, 640, 25);

    NN = new QTextEdit(group);
    NN->setGeometry(0, 740, 120, 100);
    NN->setText("Научная новизна");
    NN->setFont(QFont("Times", 9, QFont::Bold));
    NN->setReadOnly(1);
    NN_pole = new QTextEdit(group);
    NN_pole->setGeometry(120, 740, 640, 100);

    NIR = new QTextEdit(group);
    NIR->setGeometry(0, 840, 120, 25);
    NIR->setText("НИР");
    NIR->setFont(QFont("Times", 9, QFont::Bold));
    NIR->setReadOnly(1);
    NIR_pole = new QTextEdit(group);
    NIR_pole->setGeometry(120, 840, 640, 25);

    NIOKR = new QTextEdit(group);
    NIOKR->setGeometry(0, 865, 120, 25);
    NIOKR->setText("НИОКР");
    NIOKR->setFont(QFont("Times", 9, QFont::Bold));
    NIOKR->setReadOnly(1);
    NIOKR_pole = new QTextEdit(group);
    NIOKR_pole->setGeometry(120, 865, 640, 25);

    NA = new QTextEdit(group);
    NA->setGeometry(0, 890, 120, 85);
    NA->setText("Наличие аналогов");
    NA->setFont(QFont("Times", 9, QFont::Bold));
    NA->setReadOnly(1);

    NA_pole = new QTextEdit(group);
    NA_pole->setGeometry(120, 890, 640, 85);

    PD = new QTextEdit(group);
    PD->setGeometry(0, 975, 120, 115);
    PD->setText("Правоустанавли-вающие документы\n\n\n\nДругое(укажите)");
    PD->setFont(QFont("Times", 9, QFont::Bold));
    PD->setReadOnly(1);

    P = new QTextEdit(group);
    P->setGeometry(120, 975, 80, 45);
    P->setText("Патент");
    P->setFont(QFont("Times", 9, QFont::Bold));
    P->setReadOnly(1);
    P_pole = new QTextEdit(group);
    P_pole->setGeometry(200, 975, 230, 45);
    S = new QTextEdit(group);
    S->setGeometry(430, 975, 100, 45);
    S->setText("Сертификат");
    S->setFont(QFont("Times", 9, QFont::Bold));
    S->setReadOnly(1);
    S_pole = new QTextEdit(group);
    S_pole->setGeometry(530, 975, 230, 45);

    L = new QTextEdit(group);
    L->setGeometry(120, 1020, 80, 45);
    L->setText("Лицензия");
    L->setFont(QFont("Times", 9, QFont::Bold));
    L->setReadOnly(1);
    L_pole = new QTextEdit(group);
    L_pole->setGeometry(200, 1020, 230, 45);
    SV = new QTextEdit(group);
    SV->setGeometry(430, 1020, 100, 45);
    SV->setText("Свидетельство");
    SV->setFont(QFont("Times", 9, QFont::Bold));
    SV->setReadOnly(1);
    SV_pole = new QTextEdit(group);
    SV_pole->setGeometry(530, 1020, 230, 45);

    Dr = new QTextEdit(group);
    Dr->setGeometry(120, 1065, 640, 25);

    createConnections();
}

void FormDialog::createConnections() {
    connect (save, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect (print, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect (cancel, SIGNAL(clicked()), this, SLOT(slotButton()));
}

void FormDialog::slotButton() {
    if (sender() == save) {
        QFile file("forms/"+N_pole->toPlainText()+".txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
        QTextStream out(&file);
        out<<NR_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<DN_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<DO_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<A_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<KS_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<OF_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<SNR_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<R_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<I_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<ma_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<prib_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<mat_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<t_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<meh_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<ps_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<u_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<prod_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<dru_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<O_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<NN_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<NIR_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<NIOKR_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<NA_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<P_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<S_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<L_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<SV_pole->toPlainText().remove(QChar(9));
        out<<QChar(9);
        out<<Dr->toPlainText().remove(QChar(9));
        file.close();
    }
    if (sender() == print) {
        QPrinter printer;
        QPrintPreviewDialog preview(&printer, group);
        connect(&preview, SIGNAL(paintRequested(QPrinter *) ), this, SLOT(printDocument(QPrinter *)));
        preview.setGeometry(40, 40, 500, 700);
        preview.exec();
    }
    if (sender() == cancel) {
        this->close();
    }
}

void FormDialog::read(QString name) {
    QFile file("forms/" + name + ".txt");
    if (!file.open(QIODevice::ReadOnly))
             return;
    QString s = file.readAll();
    QStringList information = s.split(QChar(9));
    N_pole->setText(name);
    NR_pole->setText(information[0]);
    DN_pole->setText(information[1]);
    DO_pole->setText(information[2]);
    A_pole->setText(information[3]);
    KS_pole->setText(information[4]);
    OF_pole->setText(information[5]);
    SNR_pole->setText(information[6]);
    R_pole->setText(information[7]);
    I_pole->setText(information[8]);
    ma_pole->setText(information[9]);
    prib_pole->setText(information[10]);
    mat_pole->setText(information[11]);
    t_pole->setText(information[12]);
    meh_pole->setText(information[13]);
    ps_pole->setText(information[14]);
    u_pole->setText(information[15]);
    prod_pole->setText(information[16]);
    dru_pole->setText(information[17]);
    O_pole->setText(information[18]);
    NN_pole->setText(information[19]);
    NIR_pole->setText(information[20]);
    NIOKR_pole->setText(information[21]);
    NA_pole->setText(information[22]);
    P_pole->setText(information[23]);
    S_pole->setText(information[24]);
    L_pole->setText(information[25]);
    SV_pole->setText(information[26]);
    Dr->setText(information[27]);
    file.close();
}

void FormDialog::printDocument(QPrinter *printer_) {
    if (group != NULL) {
        group->render(printer_);
    }
}

FormDialog::~FormDialog()
{

}

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(400, 400);
    combo = new QComboBox(this);
    request = new QTextEdit(this);
    list = new QListWidget(this);
    open = new QPushButton("Открыть", this);
    filtr = new QPushButton("Фильтровать", this);
    cancel = new QPushButton("Отмена", this);

    combo->setGeometry(25, 25, 350, 25);
    request->setGeometry(25, 75, 350, 25);
    list->setGeometry(25, 125, 350, 200);
    open->setGeometry(25, 350, 100, 25);
    filtr->setGeometry(150, 350, 100, 25);
    cancel->setGeometry(275, 350, 100, 25);

    QStringList categories(QStringList()<<"Название"
                           <<"Номер регистрации"
                           <<"Дата начала"
                           <<"Дата окончания"
                           <<"Аннотация"
                           <<"Ключевые слова"
                           <<"Финансирование"
                           <<"Сфера научных разработок"
                           <<"Руководитель"
                           <<"Исполнители"
                           <<"методика, алгоритм"
                           <<"прибор"
                           <<"материал"
                           <<"технология"
                           <<"механизм"
                           <<"программное средство"
                           <<"устройство"
                           <<"продукт"
                           <<"другое"
                           <<"Описание"
                           <<"Научная новизна"
                           <<"НИР"
                           <<"НИОКР"
                           <<"Наличие аналогов"
                           <<"Патент"
                           <<"Сертификат"
                           <<"Лицензия"
                           <<"Свидетельство"
                           <<"Другое");
    combo->addItems(categories);
    QDir Dir;
    Dir.cd("forms");
    QStringList listFiles = Dir.entryList(QStringList()<<"*", QDir::Files);
    for (int i = 0; i < listFiles.size(); ++i) {
        listFiles[i].remove(-4, 4);
    }
    list->addItems(listFiles);

    createConnections();
}

void FindDialog::createConnections() {
    connect (open, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect (filtr, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect (cancel, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect (combo, SIGNAL(activated(int)), this, SLOT(slotCombo(int)));
}

void FindDialog::slotButton() {
    if (sender() == open) {
        if (list->currentItem() != NULL) {
            FormDialog d;
            d.setWindowTitle("Form");
            d.read(list->currentItem()->text());
            d.exec();
        }
    }
    if (sender() == filtr) {
        list->clear();
        QDir Dir;
        Dir.cd("forms");
        QStringList listFiles = Dir.entryList(QStringList()<<"*", QDir::Files);
        QStringList finds;
        for (int i = 0; i < listFiles.size(); ++i) {
            listFiles[i].remove(-4, 4);
            QFile file("forms/"+listFiles[i]+".txt");
            if (!file.open(QIODevice::ReadOnly))
                     return;
            QString s = listFiles[i] + QChar(9) + file.readAll();
            QStringList information = s.split(QChar(9));
            if (information[combo->currentIndex()].contains(request->toPlainText())) {
                finds.append(listFiles[i]);
            }
            file.close ();
        }
        list->addItems(finds);
    }
    if (sender() == cancel) {
        this->close();
    }
}

void FindDialog::slotCombo(int k)
{
    if (sender() == combo) {

    }
}

FindDialog::~FindDialog()
{

}
