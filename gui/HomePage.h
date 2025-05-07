#pragma once 

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QMainWindow> 

class HomePage : public QMainWindow {
    Q_OBJECT

public:
    HomePage(QWidget *parent = nullptr);

private slots:
    void showLogin();
    void showSignup();
    void returnToHome();

private:
    void setupHomeScreen();
    void setupLoginScreen();
    void setupSignupScreen();
    void fadeWidgets(QWidget* toHide, QWidget* toShow);

    QWidget *homeWidget;
    QWidget *loginWidget;
    QWidget *signupWidget;
    QStackedWidget *stackedWidget;
    
    // Home screen elements
    QLabel *title;
    QPushButton *loginBtn;
    QPushButton *signupBtn;
};