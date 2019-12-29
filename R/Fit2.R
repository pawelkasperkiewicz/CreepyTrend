#' @export

Fit <- function(CreepyTrend, parallel = T){

  if(!is(CreepyTrend, "CreepyTrend")){
    stop("First argument of function Fit must be CreepyTrend S4 class. Create it using CreepyTrend() function")
  }


  Models <- map(CreepyTrend@k, function(x){


  n <- length(CreepyTrend@series)
  indexes <- vector("list", n - x + 1)
  y <- 0
  indexes <- lapply(indexes, function(z){
    y <<- 1 + y
    seq(y, length.out = x)
  })

  if(parallel){
    Clust <- makePSOCKcluster(detectCores())
    junk <- clusterEvalQ(Clust, library(CreepyTrend))
    clusterExport(cl = Clust, varlist = list("CreepyTrend"))
    Partial <- parLapply(Clust, indexes, function(x){
      Frame <- data.table(Values = fastLm(CreepyTrend@series[x] ~ x)$fitted.values, Index = x)
    })
    Partial <- rbindlist(Partial, fill = T)
    Partial <- Partial[ ,mean(Values, na.rm = T), by = Index][ ,.(V1)]
    setnames(Partial, "V1", paste0("k_", x))
    stopCluster(Clust)
    gc()
    return(Partial)
  }
  }) %>% Reduce(cbind, .)





  # if(!parallel){
  #   Partial <- Lapply(indexes, function(x){
  #     Frame <- data.table(Values = fastLm(CreepyTrend@series[x] ~ x)$fitted.values, Index = x)
  #   })
  #   Partial <- rbindlist(Partial, fill = T)
  #   CreepyTrend@fitted <- Partial[ ,mean(Values, na.rm = T), by = Index]
  #   gc()
  #   return(CreepyTrend)
  # }else(
  #   stop("Parallel must be logical - TRUE or FALSE")
  # )

}


