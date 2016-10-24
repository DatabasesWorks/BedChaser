#include "editfacilitydialog.h"
#include "ui_editfacilitydialog.h"

#include "patientlistdialog.h"
#include "facility.h"
#include "datamanager.h"
#include "exception.h"

EditFacilityDialog::EditFacilityDialog(const QSharedPointer<Facility> &facility, QWidget *parent) :
    QDialog(parent), ui(new Ui::EditFacilityDialog)
{
    ui->setupUi(this);

    this->facility = facility;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EditFacilityDialog::updateFacility);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EditFacilityDialog::close);

    ui->ACSpin->setValue(facility->getNumberOfAcuteCareBeds());
    ui->LTCSpin->setValue(facility->getNumberOfLongTermCareBeds());
    ui->CCCSpin->setValue(facility->getNumberOfComplexContinuingCareBeds());
    ui->name->setText(facility->getName());
    ui->x->setNum(facility->getX());
    ui->y->setNum(facility->getY());
}

EditFacilityDialog::~EditFacilityDialog()
{
    delete ui;
}

void EditFacilityDialog::updateFacility()
{
    try
    {
        facility->setNumberOfAcuteCareBeds(ui->ACSpin->value());
        facility->setNumberOfComplexContinuingCareBeds(ui->CCCSpin->value());
        facility->setNumberOfLongTermCareBeds(ui->LTCSpin->value());
        facility->setName(ui->name->text());
        facility->setX(ui->x->text().toInt());
        facility->setY(ui->y->text().toInt());

        DataManager::sharedInstance().updateFacility(*facility);
    }
    catch(Exception &e)
    {
        // TODO
    }

    close();
}

void EditFacilityDialog::on_patientlist_clicked()
{
    PatientListDialog wf(facility, this);
    wf.exec();
}