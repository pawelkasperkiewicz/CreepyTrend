#' @exportClass Params
setClass("Params", representation(k = "integer"))


#' @exportClass CreepyTrend
CreepyTrend <- setClass("CreepyTrend", representation(series = "numeric", k = "vector", AICc = "numeric", residuals = "numeric", fitted = "data.frame",
                                                      prediction = "numeric"))
