#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    ui->tableView->setStyleSheet(
        "QTableView::item {"
        "    border-bottom: 1px solid white;}"
        "QTableView {"
        "   background-color: black;}"
        );

    ui->tableView->setModel(model);

    model->setHorizontalHeaderLabels({"Name", "Phone", "Email"});
    ui->tableView->setColumnWidth(0, 150); // Name column
    ui->tableView->setColumnWidth(1, 100); // Phone column
    ui->tableView->setColumnWidth(2, 200); // Email column

    contacts = {
        {"Neo Medrano", "123-456-7890", "neomedrano@gmail.com"},
        {"Junio Layba", "234-567-8901", "joni@gmail.com"},
        {"Ron Vincent Cada", "345-678-9012", "cronvincent@gmail.com"},
        {"Gabriel Ballesteros", "456-789-0123", "ballesterosgab@gmail.com"},
        {"Peter Bob Domogma", "567-890-1234", "peterparker@gmail.com"},
        {"Mike Andrei Gomez", "678-901-2345", "gomezmike@gmail.com"},
        {"Eyre Vincent Gonzales", "789-012-3456", "coachEyre@gmail.com"}
    };

    updateTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    Contact contact;
    contact.name = ui->nameLineEdit->text();
    contact.phone = ui->phoneLineEdit->text();
    contact.email = ui->emailLineEdit->text();

    contacts.push_back(contact);
    updateTableView();
}

void MainWindow::on_editButton_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if (selected.count() > 0) {
        int row = selected.at(0).row();
        contacts[row].name = ui->nameLineEdit->text();
        contacts[row].phone = ui->phoneLineEdit->text();
        contacts[row].email = ui->emailLineEdit->text();
        updateTableView();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    for (const QModelIndex &index : selected) {
        contacts.erase(contacts.begin() + index.row());
    }
    updateTableView();
}

void MainWindow::updateTableView()
{
    model->removeRows(0, model->rowCount());
    for (const Contact &contact : contacts) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(contact.name));
        items.append(new QStandardItem(contact.phone));
        items.append(new QStandardItem(contact.email));
        model->appendRow(items);
    }
}
