/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QHBoxLayout *horizontalLayout;
    QLCDNumber *lcd_pout;
    QLCDNumber *lcd_vout;
    QLCDNumber *lcd_iout;
    QPushButton *btn_output;
    QDial *dial_iout;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btn_flash;
    QComboBox *cmb_port_name;
    QComboBox *cmb_baud_rate;
    QPushButton *btn_connect;
    QPushButton *btn_disconnect;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_2;
    QLineEdit *lint_send_data;
    QPushButton *btn_send;
    QGroupBox *groupBox_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lint_send_data_2;
    QLineEdit *lint_send_data_3;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lint_send_data_4;
    QLineEdit *lint_send_data_5;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lint_send_data_6;
    QLineEdit *lint_send_data_7;
    QPushButton *pushButton_3;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *lint_send_data_8;
    QLineEdit *lint_send_data_9;
    QPushButton *pushButton_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *lint_send_data_10;
    QLineEdit *lint_send_data_11;
    QPushButton *pushButton_5;
    QDial *dial_vout;
    QLabel *lab_vset;
    QLabel *lab_iset;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1059, 623);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 10, 871, 141));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label1 = new QLabel(verticalLayoutWidget);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setTextFormat(Qt::AutoText);
        label1->setScaledContents(false);
        label1->setAlignment(Qt::AlignCenter);
        label1->setMargin(0);
        label1->setIndent(-1);
        label1->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_2->addWidget(label1);

        label2 = new QLabel(verticalLayoutWidget);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setTextFormat(Qt::AutoText);
        label2->setScaledContents(false);
        label2->setAlignment(Qt::AlignCenter);
        label2->setMargin(0);
        label2->setIndent(-1);
        label2->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_2->addWidget(label2);

        label3 = new QLabel(verticalLayoutWidget);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setTextFormat(Qt::AutoText);
        label3->setScaledContents(false);
        label3->setAlignment(Qt::AlignCenter);
        label3->setMargin(0);
        label3->setIndent(-1);
        label3->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_2->addWidget(label3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lcd_pout = new QLCDNumber(verticalLayoutWidget);
        lcd_pout->setObjectName(QStringLiteral("lcd_pout"));

        horizontalLayout->addWidget(lcd_pout);

        lcd_vout = new QLCDNumber(verticalLayoutWidget);
        lcd_vout->setObjectName(QStringLiteral("lcd_vout"));
        lcd_vout->setSmallDecimalPoint(false);

        horizontalLayout->addWidget(lcd_vout);

        lcd_iout = new QLCDNumber(verticalLayoutWidget);
        lcd_iout->setObjectName(QStringLiteral("lcd_iout"));

        horizontalLayout->addWidget(lcd_iout);


        verticalLayout->addLayout(horizontalLayout);

        btn_output = new QPushButton(centralwidget);
        btn_output->setObjectName(QStringLiteral("btn_output"));
        btn_output->setGeometry(QRect(910, 500, 111, 51));
        btn_output->setIconSize(QSize(32, 32));
        dial_iout = new QDial(centralwidget);
        dial_iout->setObjectName(QStringLiteral("dial_iout"));
        dial_iout->setGeometry(QRect(310, 220, 250, 250));
        dial_iout->setMaximum(5000);
        dial_iout->setWrapping(false);
        dial_iout->setNotchTarget(0.7);
        dial_iout->setNotchesVisible(true);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(910, 50, 121, 311));
        verticalLayoutWidget_2 = new QWidget(groupBox);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 30, 121, 281));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_flash = new QPushButton(verticalLayoutWidget_2);
        btn_flash->setObjectName(QStringLiteral("btn_flash"));
        btn_flash->setIconSize(QSize(32, 32));

        verticalLayout_2->addWidget(btn_flash);

        cmb_port_name = new QComboBox(verticalLayoutWidget_2);
        cmb_port_name->setObjectName(QStringLiteral("cmb_port_name"));

        verticalLayout_2->addWidget(cmb_port_name);

        cmb_baud_rate = new QComboBox(verticalLayoutWidget_2);
        cmb_baud_rate->setObjectName(QStringLiteral("cmb_baud_rate"));

        verticalLayout_2->addWidget(cmb_baud_rate);

        btn_connect = new QPushButton(verticalLayoutWidget_2);
        btn_connect->setObjectName(QStringLiteral("btn_connect"));
        btn_connect->setIconSize(QSize(32, 32));

        verticalLayout_2->addWidget(btn_connect);

        btn_disconnect = new QPushButton(verticalLayoutWidget_2);
        btn_disconnect->setObjectName(QStringLiteral("btn_disconnect"));
        btn_disconnect->setIconSize(QSize(32, 32));

        verticalLayout_2->addWidget(btn_disconnect);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 470, 531, 91));
        lint_send_data = new QLineEdit(groupBox_2);
        lint_send_data->setObjectName(QStringLiteral("lint_send_data"));
        lint_send_data->setGeometry(QRect(0, 20, 391, 71));
        btn_send = new QPushButton(groupBox_2);
        btn_send->setObjectName(QStringLiteral("btn_send"));
        btn_send->setGeometry(QRect(410, 50, 80, 31));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(570, 170, 311, 411));
        widget = new QWidget(groupBox_3);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 30, 291, 361));
        verticalLayout_8 = new QVBoxLayout(widget);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lint_send_data_2 = new QLineEdit(widget);
        lint_send_data_2->setObjectName(QStringLiteral("lint_send_data_2"));

        horizontalLayout_3->addWidget(lint_send_data_2);

        lint_send_data_3 = new QLineEdit(widget);
        lint_send_data_3->setObjectName(QStringLiteral("lint_send_data_3"));

        horizontalLayout_3->addWidget(lint_send_data_3);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lint_send_data_4 = new QLineEdit(widget);
        lint_send_data_4->setObjectName(QStringLiteral("lint_send_data_4"));

        horizontalLayout_6->addWidget(lint_send_data_4);

        lint_send_data_5 = new QLineEdit(widget);
        lint_send_data_5->setObjectName(QStringLiteral("lint_send_data_5"));

        horizontalLayout_6->addWidget(lint_send_data_5);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_6->addWidget(pushButton_2);


        verticalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_7->addWidget(label_8);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_7->addWidget(label_9);


        verticalLayout_5->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        lint_send_data_6 = new QLineEdit(widget);
        lint_send_data_6->setObjectName(QStringLiteral("lint_send_data_6"));

        horizontalLayout_8->addWidget(lint_send_data_6);

        lint_send_data_7 = new QLineEdit(widget);
        lint_send_data_7->setObjectName(QStringLiteral("lint_send_data_7"));

        horizontalLayout_8->addWidget(lint_send_data_7);

        pushButton_3 = new QPushButton(widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_8->addWidget(pushButton_3);


        verticalLayout_5->addLayout(horizontalLayout_8);


        verticalLayout_8->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_9->addWidget(label_10);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_9->addWidget(label_11);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_9->addWidget(label_12);


        verticalLayout_6->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        lint_send_data_8 = new QLineEdit(widget);
        lint_send_data_8->setObjectName(QStringLiteral("lint_send_data_8"));

        horizontalLayout_10->addWidget(lint_send_data_8);

        lint_send_data_9 = new QLineEdit(widget);
        lint_send_data_9->setObjectName(QStringLiteral("lint_send_data_9"));

        horizontalLayout_10->addWidget(lint_send_data_9);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_10->addWidget(pushButton_4);


        verticalLayout_6->addLayout(horizontalLayout_10);


        verticalLayout_8->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_11->addWidget(label_13);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_11->addWidget(label_14);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_11->addWidget(label_15);


        verticalLayout_7->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        lint_send_data_10 = new QLineEdit(widget);
        lint_send_data_10->setObjectName(QStringLiteral("lint_send_data_10"));

        horizontalLayout_12->addWidget(lint_send_data_10);

        lint_send_data_11 = new QLineEdit(widget);
        lint_send_data_11->setObjectName(QStringLiteral("lint_send_data_11"));

        horizontalLayout_12->addWidget(lint_send_data_11);

        pushButton_5 = new QPushButton(widget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout_12->addWidget(pushButton_5);


        verticalLayout_7->addLayout(horizontalLayout_12);


        verticalLayout_8->addLayout(verticalLayout_7);

        dial_vout = new QDial(centralwidget);
        dial_vout->setObjectName(QStringLiteral("dial_vout"));
        dial_vout->setGeometry(QRect(30, 210, 250, 250));
        dial_vout->setLayoutDirection(Qt::LeftToRight);
        dial_vout->setAutoFillBackground(false);
        dial_vout->setInputMethodHints(Qt::ImhNone);
        dial_vout->setMaximum(3000);
        dial_vout->setTracking(true);
        dial_vout->setOrientation(Qt::Horizontal);
        dial_vout->setInvertedAppearance(false);
        dial_vout->setInvertedControls(false);
        dial_vout->setWrapping(false);
        dial_vout->setNotchTarget(0.7);
        dial_vout->setNotchesVisible(true);
        lab_vset = new QLabel(centralwidget);
        lab_vset->setObjectName(QStringLiteral("lab_vset"));
        lab_vset->setGeometry(QRect(80, 310, 151, 41));
        lab_iset = new QLabel(centralwidget);
        lab_iset->setObjectName(QStringLiteral("lab_iset"));
        lab_iset->setGeometry(QRect(360, 310, 151, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1059, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label1->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; color:#55aa00;\">\347\224\265\345\216\213</span></p></body></html>", Q_NULLPTR));
        label2->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; color:#ff0000;\">\347\224\265\346\265\201</span></p></body></html>", Q_NULLPTR));
        label3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt; color:#00aaff;\">\345\212\237\347\216\207</span></p></body></html>", Q_NULLPTR));
        btn_output->setText(QApplication::translate("MainWindow", "\350\276\223\345\207\272", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\216\245\345\217\243\346\216\247\345\210\266\345\214\272", Q_NULLPTR));
        btn_flash->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", Q_NULLPTR));
        cmb_baud_rate->clear();
        cmb_baud_rate->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "57600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "38400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4800", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1200", Q_NULLPTR)
        );
        btn_connect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        btn_disconnect->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\344\277\241\346\201\257\346\230\276\347\244\272\345\214\272", Q_NULLPTR));
        btn_send->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\351\242\204\350\256\276\345\214\272", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\345\216\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\346\265\201", Q_NULLPTR));
        label_3->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\345\216\213", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\346\265\201", Q_NULLPTR));
        label_6->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\345\216\213", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\346\265\201", Q_NULLPTR));
        label_9->setText(QString());
        pushButton_3->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\345\216\213", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\346\265\201", Q_NULLPTR));
        label_12->setText(QString());
        pushButton_4->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\345\216\213", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\347\224\265\346\265\201", Q_NULLPTR));
        label_15->setText(QString());
        pushButton_5->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", Q_NULLPTR));
        lab_vset->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:28pt; font-weight:600; color:#00aa00;\">00.00V</span></p></body></html>", Q_NULLPTR));
        lab_iset->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:28pt; font-weight:600; color:#ff0000;\">00.00A</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
