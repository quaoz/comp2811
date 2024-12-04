#include <QApplication>
#include "compliancedashboard.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ComplianceDashboard dashboard;
    dashboard.show();
    return app.exec();
}
