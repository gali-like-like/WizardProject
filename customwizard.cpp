#include "customwizard.h"

CustomWizard::CustomWizard(QWidget *parent)
    : QWizard(parent)
{
    setTitleFormat(Qt::MarkdownText);
    setSubTitleFormat(Qt::MarkdownText);
    setWizardStyle(QWizard::AeroStyle);
//    setPixmap(QWizard::BannerPixmap,QPixmap(":/Banner.jpeg"));
    setPixmap(QWizard::LogoPixmap,QPixmap(""));
//    setPixmap(QWizard::WatermarkPixmap,QPixmap(":/Watermark.jpg"));
    addPage(new ProjectLocationPage);
    addPage(new BuildSystemPage);
    addPage(new ClassInfoPage);
    addPage(new LanguagePage);
    addPage(new BuildKitPage);
    addPage(new ProjectManagePage);
    this->setWindowTitle("  Widgets Application");
    listWidget = new QListWidget(this);
    listWidget->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Preferred);
    locationItem = new QListWidgetItem("Location",listWidget);
    buildSystemItem = new QListWidgetItem("Build System",listWidget);
    classInformationItem = new QListWidgetItem("Class Information",listWidget);
    translationItem = new QListWidgetItem("Translation",listWidget);
    buildKitItem = new QListWidgetItem("Build Kit",listWidget);
    projectManageItem = new QListWidgetItem("Project Management",listWidget);
    listWidget->addItem(locationItem);
    listWidget->addItem(buildSystemItem);
    listWidget->addItem(classInformationItem);
    listWidget->addItem(translationItem);
    listWidget->addItem(buildKitItem);
    listWidget->addItem(projectManageItem);
    listWidget->setMinimumSize(QSize(150,300));
    this->setSideWidget(listWidget);
    this->setContentsMargins(5,10,10,10);
    this->setBaseSize(QSize(500,400));
    connect(this,&CustomWizard::currentIdChanged,this,&CustomWizard::do_currentIdChanged);
    this->setItemSize();
}

void CustomWizard::setItemSize()
{
    int rowCount = listWidget->count();
    for(int i = 0;i<rowCount;i++)
    {
        QListWidgetItem* item = listWidget->item(i);
        item->setSizeHint(QSize(50,40));
        item->setTextAlignment(Qt::AlignLeft|Qt::AlignCenter);
    }
}

void CustomWizard::do_currentIdChanged(int id)
{
    listWidget->setCurrentRow(id);
}

void CustomWizard::accept()
{
    return QDialog::accept();
}

CustomWizard::~CustomWizard()
{

}

bool ProjectLocationPage::validatePage()
{
    if(!this->field("name").toString().isEmpty() && !this->field("location").toString().isEmpty())
    {
        return true;
    }
    else
        return false;
}

ProjectLocationPage::ProjectLocationPage(QWidget* parent):QWizardPage(parent)
{
    this->setTitle("Project Location");
    this->setSubTitle("#### This wizard generates a Qt Widgets Application project,"
                      " The application derives by default from QApplication "
                      "and includes an empty widget.");

    QGridLayout* gridLayout = new QGridLayout(this);
    nameLabel = new QLabel(tr("N&ame:"),this);
    locationLabel = new QLabel(tr("&Create location:"),this);
    nameLineEdit = new QLineEdit();
    nameLabel->setBuddy(nameLineEdit);
    locationLineEdit = new QLineEdit();
    locationLabel->setBuddy(locationLineEdit);
    lookUpPushButton = new QPushButton("浏览");
    frame = new QFrame(this);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Shadow::Sunken);
    defaultLocationCheckBox = new QCheckBox("设为默认项目路径");
    gridLayout->addWidget(nameLabel,0,0);
    gridLayout->addWidget(locationLabel,1,0);
    gridLayout->addWidget(nameLineEdit,0,1,1,2);
    gridLayout->addWidget(locationLineEdit,1,1);
    gridLayout->addWidget(lookUpPushButton,1,2);
    gridLayout->addWidget(defaultLocationCheckBox,2,0,2,3);
    frame->setLayout(gridLayout);
    QGridLayout* gl = new QGridLayout(this);
    gl->addWidget(frame);
    this->setLayout(gl);
//    this->setLayout(gridLayout);
    registerField("name",nameLineEdit);
    registerField("location",locationLineEdit);
    registerField("defaultLocation",defaultLocationCheckBox);
    connect(lookUpPushButton,&QPushButton::clicked,this,&ProjectLocationPage::do_lookUpClicked);

};

void ProjectLocationPage::initializePage()
{
    bool ok = this->validatePage();
    qDebug()<<"validate resulte:"<<ok;
    QAbstractButton* btn = this->wizard()->button(QWizard::NextButton);
    if(btn != nullptr)
    {
        qDebug()<<"btn is valid";
        btn->setEnabled(!ok);
        this->wizard()->setButton(QWizard::NextButton,btn);
    }
    else
        qDebug()<<"btn is invalid";
}

void ProjectLocationPage::do_lookUpClicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this,"文件选择框",QDir::currentPath());
    if(filePath.isEmpty())
    {
        return;
    }
    locationLineEdit->setText(filePath);
}

BuildSystemPage::BuildSystemPage(QWidget* parent):QWizardPage(parent)
{
    this->setTitle("Define Build System");
    buildSystemLabel = new QLabel("Build System",this);
    buildSystemLabel->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Fixed);
    buildSystemComboBox = new QComboBox(this);
    buildSystemComboBox->setSizePolicy(QSizePolicy::Policy::Preferred,QSizePolicy::Fixed);
    buildSystemComboBox->addItem("QMake");
    buildSystemComboBox->addItem("CMake");
    buildSystemComboBox->addItem("Qbs");
    QHBoxLayout* hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(buildSystemLabel);
    hBoxLayout->addWidget(buildSystemComboBox);
    this->setLayout(hBoxLayout);
    registerField("buildSystemId",buildSystemComboBox);
};

BuildSystemPage::~BuildSystemPage()
{

};

ClassInfoPage::ClassInfoPage(QWidget* parent):QWizardPage(parent)
{
    this->setTitle("Class Information");
    this->setSubTitle("Specify basic information about the classes for which you want to generate skeleton source code files.");
    QGridLayout* gridLayout = new QGridLayout(this);
    classNameLabel = new QLabel("Class name:",this);
    baseClassLabel = new QLabel("Base class:",this);
    headerFileLabel = new QLabel("Header file:",this);
    sourceFileLabel = new QLabel("Source file:",this);
    formFileLabel = new QLabel("Form File:",this);
    generatorFormCheckBox = new QCheckBox("Generate form",this);
    classNameLineEdit = new QLineEdit(this);
    baseClassComboBox = new QComboBox(this);
    headerFileLineEdit = new QLineEdit(this);
    sourceFileLineEdit = new QLineEdit(this);
    formFileLineEdit = new QLineEdit(this);
    baseClassComboBox->addItem("QMainWindow");
    baseClassComboBox->addItem("QWidget");
    baseClassComboBox->addItem("QDialog");
    gridLayout->addWidget(classNameLabel,0,0);
    gridLayout->addWidget(classNameLineEdit,0,1);
    gridLayout->addWidget(baseClassLabel,1,0);
    gridLayout->addWidget(baseClassComboBox,1,1);
    gridLayout->addWidget(headerFileLabel,2,0);
    gridLayout->addWidget(headerFileLineEdit,2,1);
    gridLayout->addWidget(sourceFileLabel,3,0);
    gridLayout->addWidget(sourceFileLineEdit,3,1);
    gridLayout->addWidget(generatorFormCheckBox,4,1);
    gridLayout->addWidget(formFileLabel,5,0);
    gridLayout->addWidget(formFileLineEdit,5,1);
    this->setLayout(gridLayout);
    connect(classNameLineEdit,&QLineEdit::editingFinished,this,&ClassInfoPage::do_classNameEditFinished);
    connect(generatorFormCheckBox,&QCheckBox::clicked,this,&ClassInfoPage::do_checkBoxToggled);
    generatorFormCheckBox->setChecked(true);
};

void ClassInfoPage::do_checkBoxToggled(bool status)
{
    formFileLineEdit->setReadOnly(!status);
}

void ClassInfoPage::do_classNameEditFinished()
{
    QString editText = classNameLineEdit->text();
    QString lowEditText = editText.toLower();
    QString cppFileText = QString("%1.cpp").arg(lowEditText);
    QString hFileText = QString("%1.h").arg(lowEditText);
    QString formFileText = QString("%1.ui").arg(lowEditText);
    headerFileLineEdit->setText(hFileText);
    sourceFileLineEdit->setText(cppFileText);
    formFileLineEdit->setText(formFileText);
}

ClassInfoPage::~ClassInfoPage() {};

LanguagePage::LanguagePage(QWidget* parent):QWizardPage(parent)
{
    this->setTitle("Translation File");
    this->setSubTitle("#### If you plan to provide translations for your project's user interface via the Ot Linquist tool,"
    " please select a language here. "
                      "A corresponding translation (.ts) file will be generated for you.");
    languageLabel = new QLabel("&Language",this);
    translationFileLabel = new QLabel("&translationFileLabel",this);
    languageComboBox = new QComboBox(this);
    languageComboBox->addItem("China");
    languageComboBox->addItem("English");
    translationLineEdit = new QLineEdit(this);
    languageLabel->setBuddy(languageComboBox);
    translationFileLabel->setBuddy(translationLineEdit);
    QGridLayout* gl = new QGridLayout(this);
    gl->addWidget(languageLabel,0,0);
    gl->addWidget(languageComboBox,0,1);
    gl->addWidget(translationFileLabel,1,0);
    gl->addWidget(translationLineEdit,1,1);
    this->setLayout(gl);
};

LanguagePage::~LanguagePage() {};

BuildKitPage::BuildKitPage(QWidget* parent):QWizardPage(parent)
{
    this->setTitle("Select Build kit");
    this->setSubTitle("The following kits can be used for project #### CustomWizard:");
    selectAllCheck = new QCheckBox("Select all kits",this);
    filterLineEdit = new QLineEdit(this);
    tableWidget = new QTableWidget(1,2,this);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setShowGrid(true);
    QTableWidgetItem* itemKit_1 = new QTableWidgetItem("Desktop Qt 6.2.4 MSVC2019 64bit");
    itemKit_1->setCheckState(Qt::Unchecked);
    itemKit_1->setTextAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QTableWidgetItem* itemKitDesc = new QTableWidgetItem("详情");
    itemKitDesc->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(0,0,itemKit_1);
    tableWidget->setItem(0,1,itemKitDesc);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->horizontalHeader()->setResizeContentsPrecision(0);
    tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    QGridLayout* gl = new QGridLayout(this);
    gl->addWidget(selectAllCheck,0,0);
    gl->addWidget(filterLineEdit,0,1);
    gl->addWidget(tableWidget,1,0,1,2);
    this->setLayout(gl);
};

BuildKitPage::~BuildKitPage() {};

ProjectManagePage::ProjectManagePage(QWidget* parent)
{
    this->setTitle("Project Management");
    subLabel = new QLabel("Add sub projects to the project",this);
    versionManageLabel = new QLabel("Add version control system",this);
    subProjectComboBox = new QComboBox(this);
    versionManageComboBox = new QComboBox(this);
    versionManageComboBox->addItem("git");
    versionManageComboBox->addItem("svn");
    labelFiles = new QLabel(this);
    configButton = new QPushButton("Configure",this);
    configButton->setSizePolicy(QSizePolicy::Policy::Fixed,QSizePolicy::Fixed);
    QGridLayout* gl = new QGridLayout(this);
    gl->addWidget(subLabel,0,0);
    gl->addWidget(subProjectComboBox,0,1,1,2);
    gl->addWidget(versionManageLabel,1,0);
    gl->addWidget(versionManageComboBox,1,1);
    gl->addWidget(configButton,1,2);
    gl->addWidget(labelFiles,2,0,9,1);
};

ProjectManagePage::~ProjectManagePage() {};
