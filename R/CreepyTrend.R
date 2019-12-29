#' @export
CreepyTrend <- function(Vector, k){
  new("CreepyTrend", k = as.integer(k), series = Vector)
}
