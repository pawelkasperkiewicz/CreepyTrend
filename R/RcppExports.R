# Generated by using Rcpp::compileAttributes() -> do not edit by hand
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#' @export
NULL

#' @export
NULL

Aggr <- function(X, Y) {
    .Call('_CreepyTrend_Aggr', PACKAGE = 'CreepyTrend', X, Y)
}

Fit <- function(x, y, l, cores) {
    .Call('_CreepyTrend_Fit', PACKAGE = 'CreepyTrend', x, y, l, cores)
}

