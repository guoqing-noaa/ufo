/*
 * (C) Copyright 2018-2019 UCAR
 * 
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0. 
 */

#ifndef UFO_FILTERS_DIAGBOUNDSCHECK_H_
#define UFO_FILTERS_DIAGBOUNDSCHECK_H_

#include <ostream>
#include <string>

#include "boost/shared_ptr.hpp"

#include "eckit/config/LocalConfiguration.h"
#include "ioda/ObsDataVector.h"
#include "ioda/ObsSpace.h"
#include "oops/base/Variables.h"
#include "oops/util/ObjectCounter.h"
#include "oops/util/Printable.h"
#include "ufo/filters/ObsFilterData.h"

namespace ioda {
  template <typename DATATYPE> class ObsDataVector;
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsDiagnostics;

/// DiagBoundsCheck: generic quality control based on diagnostic data only

// Check that observations are within some bounds over some domain

class DiagBoundsCheck : public util::Printable,
                        private util::ObjectCounter<DiagBoundsCheck> {
 public:
  static const std::string classname() {return "ufo::DiagBoundsCheck";}

  DiagBoundsCheck(ioda::ObsSpace &, const eckit::Configuration &,
                  boost::shared_ptr<ioda::ObsDataVector<int> >,
                  boost::shared_ptr<ioda::ObsDataVector<float> >);
  ~DiagBoundsCheck();

  void preProcess() const {}
  void priorFilter(const GeoVaLs &) const;
  void postFilter(const ioda::ObsVector &, const ObsDiagnostics &) const;

  const oops::Variables & requiredGeoVaLs() const {return geovars_;}
  const oops::Variables & requiredHdiagnostics() const {return diagvars_;}

 private:
  void print(std::ostream &) const;

  ioda::ObsSpace & obsdb_;
  mutable ObsFilterData data_;
  const eckit::LocalConfiguration config_;
  const oops::Variables geovars_;
  oops::Variables diagvars_;
  ioda::ObsDataVector<int> & flags_;
};

}  // namespace ufo

#endif  // UFO_FILTERS_DIAGBOUNDSCHECK_H_