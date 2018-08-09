#ifndef POINCARE_SEQUENCE_H
#define POINCARE_SEQUENCE_H

#include <poincare/layout_helper.h>
#include <poincare/static_hierarchy.h>
#include <poincare/approximation_helper.h>

namespace Poincare {

class Sequence : public StaticHierarchy<3>  {
  using StaticHierarchy<3>::StaticHierarchy;
private:
  LayoutRef createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override;
  int serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const override {
    return SerializationHelper::Prefix(this, buffer, bufferSize, floatDisplayMode, numberOfSignificantDigits, name());
  }
  virtual LayoutRef createSequenceLayout(LayoutRef subscriptLayout, LayoutRef superscriptLayout, LayoutRef argumentLayout) const = 0;
  virtual const char * name() const = 0;
  /* Evaluation */
  Evaluation<float> approximate(SinglePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override { return templatedApproximate<float>(context, angleUnit); }
  Evaluation<double> approximate(DoublePrecision p, Context& context, Preferences::AngleUnit angleUnit) const override { return templatedApproximate<double>(context, angleUnit); }
 template<typename T> Evaluation<T> templatedApproximate(Context& context, Preferences::AngleUnit angleUnit) const;
  virtual int emptySequenceValue() const = 0;
  virtual Evaluation<float> evaluateWithNextTerm(SinglePrecision p, Evaluation<float> * a, Evaluation<float> * b) const = 0;
  virtual Evaluation<double> evaluateWithNextTerm(DoublePrecision p, Evaluation<double> * a, Evaluation<double> * b) const = 0;
};

}

#endif
