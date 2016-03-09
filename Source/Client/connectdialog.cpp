#include "connectdialog.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>

ConnectDialog::ConnectDialog(QWidget *parent) : QDialog(parent)
{
    m_lineEdit = new QLineEdit(this);

    QPushButton *searchButton = new QPushButton(tr("Search"));
    searchButton->setDefault(true);

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(searchButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *lt = new QVBoxLayout;
    lt->addWidget(m_lineEdit);
    lt->addWidget(buttonBox);

    setLayout(lt);
}
