#' @export
CreepyTrend <- R6Class("CreepyTrend",

  public = list(
    initialize = function(x){
    #TODO add tests for type of inputed values
    private$x <- x
  },

  fit = function(l){
    private$fitted = as.data.table(Fit(
      x = 101:(length(private$x)+100),
      y = private$x,
      l = l,
      cores = parallel::detectCores()
    ))[ , .(y = mean(y)), x]
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
