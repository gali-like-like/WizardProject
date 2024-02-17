#ifndef CUSTOMWIZARD_H
#define CUSTOMWIZARD_H

#include <QDialog>
#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QComboBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QListWidget>
class CustomWizard : public QWizard
{
    Q_OBJECT

public:
    CustomWizard(QWidget *parent = nullptr);
    ~CustomWizard();
    void accept() override;
private slots:
    void do_currentIdChanged(int id);
private:
    void setItemSize();
    QListWidget* listWidget;
    QListWidgetItem* locationItem;
    QListWidgetItem* buildSystemItem;
    QListWidgetItem* classInformationItem;
    QListWidgetItem* translationItem;
    QListWidgetItem* buildKitItem;
    QListWidgetItem* projectManageItem;
};

class ProjectLocationPage : public QWizardPage
{
    Q_OBJECT

public:
    ProjectLocationPage(QWidget* parent = nullptr);

private slots:
    void do_lookUpClicked();
private:
    bool validatePage();
    void initializePage();
    QLabel* nameLabel;
    QLabel* locationLabel;
    QLineEdit* nameLineEdit;
    QLineEdit* locationLineEdit;
    QCheckBox* defaultLocationCheckBox;
    QPushButton* lookUpPushButton;
    QFrame* frame;
};

class BuildSystemPage : public QWizardPage
{
    Q_OBJECT

public:
    BuildSystemPage(QWidget* parent = nullptr);

    ~BuildSystemPage();
private:
    QLabel* buildSystemLabel;
    QComboBox* buildSystemComboBox;

};

class ClassInfoPage : public QWizardPage
{
    Q_OBJECT

public:
    ClassInfoPage(QWidget* parent = nullptr);

    ~ClassInfoPage();
private slots:
    void do_classNameEditFinished();
    void do_checkBoxToggled(bool status);
private:
    QLabel* classNameLabel;
    QLabel* baseClassLabel;
    QLabel* headerFileLabel;
    QLabel* sourceFileLabel;
    QLabel* formFileLabel;
    QCheckBox* generatorFormCheckBox;
    QComboBox* baseClassComboBox;
    QLineEdit* classNameLineEdit;
    QLineEdit* headerFileLineEdit;
    QLineEdit* sourceFileLineEdit;
    QLineEdit* formFileLineEdit;

};

class LanguagePage : public QWizardPage
{
    Q_OBJECT

public:
    LanguagePage(QWidget* parent = nullptr);

    ~LanguagePage();
private slots:

private:
    QLabel* languageLabel;
    QLabel* translationFileLabel;
    QComboBox* languageComboBox;
    QLineEdit* translationLineEdit;
};

class BuildKitPage : public QWizardPage
{
    Q_OBJECT

public:
    BuildKitPage(QWidget* parent = nullptr);

    ~BuildKitPage();
private slots:

private:
    QCheckBox* selectAllCheck;
    QLineEdit* filterLineEdit;
    QTableWidget* tableWidget;
};

class ProjectManagePage : public QWizardPage
{
    Q_OBJECT

public:
    ProjectManagePage(QWidget* parent = nullptr);

    ~ProjectManagePage();
private slots:

private:
    QLabel* subLabel;
    QLabel* versionManageLabel;
    QPushButton* configButton;
    QComboBox* subProjectComboBox;
    QComboBox* versionManageComboBox;
    QLabel* labelFiles;
};

#endif // CUSTOMWIZARD_H
