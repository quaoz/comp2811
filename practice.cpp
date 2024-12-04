#include <QApplication>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "CSVReader.cpp" // Include the CSVReader class

class TableWidget : public QWidget {
public:
    TableWidget(const std::vector<RowData> &data, QWidget *parent = nullptr)
        : QWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QTableWidget *table = new QTableWidget(this);
        table->setColumnCount(3); // Assuming 3 columns for this example
        table->setHorizontalHeaderLabels({"Column 1", "Column 2", "Column 3"});
        table->setRowCount(static_cast<int>(data.size()));

        // Populate table with data
        for (int i = 0; i < static_cast<int>(data.size()); ++i) {
            table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(data[i].col1)));
            table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(data[i].col2)));
            table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(data[i].col3)));
        }

        layout->addWidget(table);
        setLayout(layout);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // File path to the CSV file
    std::string filePath = "Y-2024.csv";

    try {
        // Read the CSV file
        std::vector<RowData> data = CSVReader::readCSV(filePath);

        // Create and show the table widget
        TableWidget tableWidget(data);
        tableWidget.resize(600, 400);
        tableWidget.setWindowTitle("CSV Data Viewer");
        tableWidget.show();

        return app.exec();
    } catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return -1;
    }
}