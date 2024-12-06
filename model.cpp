// COMP2811 Coursework 2: data model

#include "model.hpp"

#include "sample.hpp"
#include "window.hpp"

void QuakeModel::updateFromFile(const QString& filename) {
  beginResetModel();
  dataset.loadData(filename.toStdString());
  endResetModel();
}

QVariant QuakeModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid()) { return QVariant(); }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignRight | Qt::AlignVCenter);
  } else if (role == Qt::DisplayRole) {
    Sample q = dataset[index.row()];
    switch (index.column()) {
      case 0: return QVariant(q.getID().c_str());
      case 1: return QVariant(q.getSamplingPoint().getID().c_str());
      case 2: return QVariant(q.getSamplingPoint().getNotation().c_str());
      case 3: return QVariant(q.getSamplingPoint().getLabel().c_str());
      case 4: return QVariant(q.getSampleDateTime().c_str());
      case 5: return QVariant(q.getDeterminand().getLabel().c_str());
      case 6: return QVariant(q.getDeterminand().getDefinition().c_str());
      case 7: return QVariant(q.getDeterminand().getNotation());
      case 8: return QVariant(q.getResultQualifier().c_str());
      case 9: return QVariant(q.getResult());
      case 10: return QVariant(q.getResultInterpretation().c_str());
      case 11: return QVariant(q.getDeterminand().getUnitLabel().c_str());
      case 12: return QVariant(q.getSampledMaterialType().c_str());
      case 13: return QVariant(q.isComplianceSample().c_str());
      case 14: return QVariant(q.getPurpose().c_str());
      case 15: return QVariant(q.getSamplingPoint().getEasting());
      case 16: return QVariant(q.getSamplingPoint().getNorthing());
      default: return QVariant();
    }
  }

  return QVariant();
}

QVariant QuakeModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
  if (role != Qt::DisplayRole) { return QVariant(); }

  if (orientation == Qt::Vertical) { return QVariant(section + 1); }

  switch (section) {
    case 0: return QString("ID");
    case 1: return QString("Sampling Point");
    case 2: return QString("Sampling Point Notation");
    case 3: return QString("Sampling Point Label");
    case 4: return QString("Sample Date Time");
    case 5: return QString("Determinand Label");
    case 6: return QString("Determinand Definition");
    case 7: return QString("Determinand Notation");
    case 8: return QString("Result Qualifier");
    case 9: return QString("Result");
    case 10: return QString("Result Interpretation");
    case 11: return QString("Determinand Unit Label");
    case 12: return QString("Sampled Material Type");
    case 13: return QString("Compliance Sample");
    case 14: return QString("Sample Purpose");
    case 15: return QString("Sampling Point Easting");
    case 16: return QString("Sampling Point Northing");
    default: return QVariant();
  }
}
<<<<<<< HEAD
=======

// void PollutantGraph::updateFromFile(const QString& filename) {
//   beginResetModel();
//   dataset.loadData(filename.toStdString());
//   endResetModel();
// }

// void PollutantGraph::data(const QModelIndex& index, int role) {
//   if (index.isValid()) {
//     Sample q = dataset[index.row()];
//     double counter = 0.0;
//     if (q.getDeterminand().getLabel() == "Endrin"){
//       //return QVariant(q.getSampleDateTime().c_str());
//       //pollutantData.qMakePair(q.getSampleDateTime(), q.getResult());
//       //pollutantData.push_back(std::make_pair(q.getSampleDateTime(), q.getResult()));
//       //pollutantData.push_back(std::make_pair(q.getSampleDateTime(), q.getResult()));
//       //pollutantData.push_back(std::make_pair(counter, q.getResult()));
//       pollutantData.append(QPointF(counter, q.getResult()));
//       counter = counter + 1.0;
//     }
//   }

// }
>>>>>>> bd0649b (init)
