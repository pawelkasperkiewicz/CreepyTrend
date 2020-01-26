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
    setnames(private$fitted, c("V1", "V2", paste0("V", 3:(length(l)+2))), c("x", "y", paste0("l", l)))
  },

  plot = function(interactive = F){
    if(nrow(private$fitted) >= 2 & require(ggplot2, quietly = T)){
      gg <- ggplot(melt(private$fitted, id.vars="x"), aes(x, value, color = variable)) + geom_line() + theme(axis.title = element_blank(), legend.title = element_blank())
    }
    if(interactive & require("plotly", quietly = T)) ggplotly(gg) else gg
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
