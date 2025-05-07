#include "HomePage.h"
#include <QScreen>
#include <QApplication>
#include <QPalette>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLineEdit>
#include <QSpinBox>
#include <QFrame>
#include <QStackedLayout>

HomePage::HomePage(QWidget *parent) 
    : QMainWindow(parent),
      stackedWidget(new QStackedWidget(this)),
      homeWidget(nullptr),
      loginWidget(nullptr),
      signupWidget(nullptr)
{
    // Window configuration
    setWindowTitle("Gym & Padel Manager");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | 
                  Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    
    // Initialize all screens
    setupHomeScreen();
    setupLoginScreen();
    setupSignupScreen();
    
    // Set stacked widget as central widget
    setCentralWidget(stackedWidget);
    
    // Show window maximized
    showMaximized();
}

void HomePage::setupHomeScreen()
{
    homeWidget = new QWidget();
    homeWidget->setStyleSheet("background-color:rgb(37, 40, 43);");  // Dark gray

    // Content container
    QWidget *contentWidget = new QWidget(homeWidget);
    contentWidget->setAttribute(Qt::WA_TranslucentBackground);

    QLabel *title = new QLabel("Welcome to Gym & Padel Manager", contentWidget);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size: 36px;"
        "color: white;"
        "font-weight: bold;"
        "background: transparent;"
        "padding: 10px;"
    );

    loginBtn = new QPushButton("Login", contentWidget);
    signupBtn = new QPushButton("Sign Up", contentWidget);

    QString buttonStyle =
        "QPushButton {"
        "   font-size: 18px;"
        "   padding: 12px 24px;"
        "   color: white;"
        "   background-color: #3498db;"
        "   border: none;"
        "   border-radius: 4px;"
        "   min-width: 200px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}";

    loginBtn->setStyleSheet(buttonStyle);
    signupBtn->setStyleSheet(buttonStyle);

    // Staff login message
    QLabel *staffLabel = new QLabel("<span style='color: white;'>Are you a staff? <a href=\"staff-login\">Sign in</a></span>", homeWidget);
    staffLabel->setTextFormat(Qt::RichText);
    staffLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    staffLabel->setOpenExternalLinks(false);
    staffLabel->setAlignment(Qt::AlignCenter);
    staffLabel->setStyleSheet("font-size: 16px; padding: 10px;");
    

    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->addStretch();
    contentLayout->addWidget(title, 0, Qt::AlignCenter);
    contentLayout->addSpacing(30);
    contentLayout->addWidget(loginBtn, 0, Qt::AlignCenter);
    contentLayout->addWidget(signupBtn, 0, Qt::AlignCenter);
    contentLayout->addStretch();


    QVBoxLayout *outerLayout = new QVBoxLayout(homeWidget);
    outerLayout->addStretch();
    outerLayout->addWidget(contentWidget, 0, Qt::AlignCenter);
    outerLayout->addStretch();
    outerLayout->addWidget(staffLabel, 0, Qt::AlignCenter);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    homeWidget->setLayout(outerLayout);

    stackedWidget->addWidget(homeWidget);

    connect(loginBtn, &QPushButton::clicked, this, &HomePage::showLogin);
    connect(signupBtn, &QPushButton::clicked, this, &HomePage::showSignup);
    connect(staffLabel, &QLabel::linkActivated, this, [this](const QString &link){
        if (link == "staff-login") {
            showLogin();
        }
    });

}

void HomePage::setupLoginScreen()
{
    loginWidget = new QWidget();
    loginWidget->setStyleSheet("background-color: rgb(37, 40, 43);");

    QVBoxLayout *layout = new QVBoxLayout(loginWidget);

    // Back button
    QPushButton *backBtn = new QPushButton("← Back", loginWidget);
    backBtn->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   padding: 8px 16px;"
        "   color: white;"
        "   background-color: transparent;"
        "   border: 1px solid white;"
        "   border-radius: 4px;"
        "}"
    );

    // Form container to restrict width
    QWidget *formContainer = new QWidget(loginWidget);
    formContainer->setMaximumWidth(500);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setAlignment(Qt::AlignCenter);

    QLabel *loginTitle = new QLabel("Login", formContainer);
    loginTitle->setStyleSheet("font-size: 36px; color: white;");
    loginTitle->setAlignment(Qt::AlignCenter);

    QLineEdit *usernameInput = new QLineEdit(formContainer);
    usernameInput->setMinimumHeight(30);
    usernameInput->setStyleSheet("font-size: 18px;");

    QLineEdit *passwordInput = new QLineEdit(formContainer);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);
    passwordInput->setStyleSheet("font-size: 18px;");


    QPushButton *submitBtn = new QPushButton("Sign In", formContainer);
    submitBtn->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   padding: 10px 20px;"
        "   background-color: #27ae60;"
        "   color: white;"
        "   border-radius: 4px;"
        "}"
    );

    formLayout->addWidget(loginTitle);
    formLayout->addSpacing(20);
    formLayout->addWidget(new QLabel("Username:", formContainer));
    formLayout->addWidget(usernameInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(new QLabel("Password:", formContainer));
    formLayout->addWidget(passwordInput);
    formLayout->addSpacing(20);
    formLayout->addWidget(submitBtn, 0, Qt::AlignCenter);

    layout->addWidget(backBtn, 0, Qt::AlignLeft);
    layout->addStretch();
    layout->addWidget(formContainer, 0, Qt::AlignCenter);
    layout->addStretch();

    loginWidget->setLayout(layout);
    stackedWidget->addWidget(loginWidget);

    connect(backBtn, &QPushButton::clicked, this, &HomePage::returnToHome);
}


void HomePage::setupSignupScreen()
{
    signupWidget = new QWidget();
    signupWidget->setStyleSheet("background-color: rgb(37, 40, 43);");

    QVBoxLayout *layout = new QVBoxLayout(signupWidget);

    // Back button
    QPushButton *backBtn = new QPushButton("← Back", signupWidget);
    backBtn->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   padding: 8px 16px;"
        "   color: white;"
        "   background-color: transparent;"
        "   border: 1px solid white;"
        "   border-radius: 4px;"
        "}"
    );

    // Form container to restrict width
    QWidget *formContainer = new QWidget(signupWidget);
    formContainer->setMaximumWidth(500);
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->setAlignment(Qt::AlignCenter);

    QLabel *signupTitle = new QLabel("Create Account", formContainer);
    signupTitle->setStyleSheet("font-size: 36px; color: white;");
    signupTitle->setAlignment(Qt::AlignCenter);

    QLineEdit *usernameInput = new QLineEdit(formContainer);
    usernameInput->setMinimumHeight(30);
    usernameInput->setStyleSheet("font-size: 18px;");

    QLineEdit *passwordInput = new QLineEdit(formContainer);
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setMinimumHeight(30);
    passwordInput->setStyleSheet("font-size: 18px;");

    QLineEdit *nameInput = new QLineEdit(formContainer);
    nameInput->setMinimumHeight(30);
    nameInput->setStyleSheet("font-size: 18px;");

    QSpinBox *ageInput = new QSpinBox(formContainer);
    ageInput->setRange(12, 100);
    ageInput->setMinimumHeight(30);
    ageInput->setStyleSheet("font-size: 18px;");


    QPushButton *submitBtn = new QPushButton("Register", formContainer);
    submitBtn->setStyleSheet(
        "QPushButton {"
        "   font-size: 16px;"
        "   padding: 10px 20px;"
        "   background-color: #27ae60;"
        "   color: white;"
        "   border-radius: 4px;"
        "}"
    );

    formLayout->addWidget(signupTitle);
    formLayout->addSpacing(20);
    formLayout->addWidget(new QLabel("Username:", formContainer));
    formLayout->addWidget(usernameInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(new QLabel("Password:", formContainer));
    formLayout->addWidget(passwordInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(new QLabel("Full Name:", formContainer));
    formLayout->addWidget(nameInput);
    formLayout->addSpacing(10);
    formLayout->addWidget(new QLabel("Age:", formContainer));
    formLayout->addWidget(ageInput);
    formLayout->addSpacing(20);
    formLayout->addWidget(submitBtn, 0, Qt::AlignCenter);

    layout->addWidget(backBtn, 0, Qt::AlignLeft);
    layout->addStretch();
    layout->addWidget(formContainer, 0, Qt::AlignCenter);
    layout->addStretch();

    signupWidget->setLayout(layout);
    stackedWidget->addWidget(signupWidget);

    connect(backBtn, &QPushButton::clicked, this, &HomePage::returnToHome);
}


void HomePage::fadeWidgets(QWidget* toHide, QWidget* toShow)
{
    QGraphicsOpacityEffect *fadeOut = new QGraphicsOpacityEffect(toHide);
    QGraphicsOpacityEffect *fadeIn = new QGraphicsOpacityEffect(toShow);
    
    toHide->setGraphicsEffect(fadeOut);
    toShow->setGraphicsEffect(fadeIn);
    
    fadeOut->setOpacity(1.0);
    fadeIn->setOpacity(0.0);
    
    QPropertyAnimation *fadeOutAnim = new QPropertyAnimation(fadeOut, "opacity");
    fadeOutAnim->setDuration(300);
    fadeOutAnim->setStartValue(1.0);
    fadeOutAnim->setEndValue(0.0);
    
    QPropertyAnimation *fadeInAnim = new QPropertyAnimation(fadeIn, "opacity");
    fadeInAnim->setDuration(300);
    fadeInAnim->setStartValue(0.0);
    fadeInAnim->setEndValue(1.0);
    
    connect(fadeOutAnim, &QPropertyAnimation::finished, [this, toHide, toShow]() {
        stackedWidget->setCurrentWidget(toShow);
    });
    
    fadeOutAnim->start(QPropertyAnimation::DeleteWhenStopped);
    fadeInAnim->start(QPropertyAnimation::DeleteWhenStopped);
}

void HomePage::showLogin()
{
    fadeWidgets(homeWidget, loginWidget);
}

void HomePage::showSignup()
{
    fadeWidgets(homeWidget, signupWidget);
}

void HomePage::returnToHome()
{
    fadeWidgets(stackedWidget->currentWidget(), homeWidget);
}