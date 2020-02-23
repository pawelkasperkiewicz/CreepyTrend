// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// Aggr
arma::colvec Aggr(const arma::colvec& X, const arma::colvec& Y);
RcppExport SEXP _CreepyTrend_Aggr(SEXP XSEXP, SEXP YSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::colvec& >::type X(XSEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type Y(YSEXP);
    rcpp_result_gen = Rcpp::wrap(Aggr(X, Y));
    return rcpp_result_gen;
END_RCPP
}
// Fit
arma::mat Fit(const arma::colvec& x, const arma::colvec& y, arma::colvec& l, int cores);
RcppExport SEXP _CreepyTrend_Fit(SEXP xSEXP, SEXP ySEXP, SEXP lSEXP, SEXP coresSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const arma::colvec& >::type x(xSEXP);
    Rcpp::traits::input_parameter< const arma::colvec& >::type y(ySEXP);
    Rcpp::traits::input_parameter< arma::colvec& >::type l(lSEXP);
    Rcpp::traits::input_parameter< int >::type cores(coresSEXP);
    rcpp_result_gen = Rcpp::wrap(Fit(x, y, l, cores));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_CreepyTrend_Aggr", (DL_FUNC) &_CreepyTrend_Aggr, 2},
    {"_CreepyTrend_Fit", (DL_FUNC) &_CreepyTrend_Fit, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_CreepyTrend(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
