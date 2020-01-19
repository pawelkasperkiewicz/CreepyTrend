#' @export
CreepyTrend <- R6Class("CreepyTrend",

  public = list(
    initialize = function(x){
    #TODO add tests for type of inputed values
    private$x <- x
  },

  fit = function(l){
    private$fitted = as.data.table(Fit(
      x = 1:length(private$x),
      y = private$x,
      l = l,
      cores = parallel::detectCores()
    ))
    setnames(private$fitted, c("V1", paste0("V", 2:(length(l)+1))), c("x", paste0("l", l)))
  }

  ),

  private = list(
    x = NA,
    k = NA,
    fitted = NA
  ),

  active = list(
    smoothed = function() return(private$fitted)
  )

)
