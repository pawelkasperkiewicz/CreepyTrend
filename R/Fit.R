#' @export

Fit <- function(CreepyTrend, parallel = "cluster"){

  if(!is(CreepyTrend, "CreepyTrend")){
    stop("First argument of function Fit must be CreepyTrend S4 class. Create it using CreepyTrend() function")
  }


  n <- length(CreepyTrend@series)
  indexes <- vector("list", n - CreepyTrend@k + 1)
  y <- 0
  indexes <- lapply(indexes, function(x){
    y <<- 1 + y
    seq(y, length.out = CreepyTrend@k)
  })

  if(parallel == "cluster"){
    Clust <- makePSOCKcluster(detectCores())
    junk <- clusterEvalQ(Clust, library(RcppArmadillo))
    junk <- clusterEvalQ(Clust, library(data.table))
    Partial <- parLapply(Clust, indexes, function(x){
      Frame <- data.table(Values = fastLm(CreepyTrend@series[x] ~ x)$fitted.values, Index = x)
    })
    Partial <- rbindlist(Partial, fill = T)
    CreepyTrend@fitted <- Partial[ ,mean(Values, na.rm = T), by = Index]
    stopCluster(Clust)
    gc()
    return(CreepyTrend)
    }

  if(parallel == "none"){
    Partial <- Lapply(indexes, function(x){
      Frame <- data.table(Values = fastLm(CreepyTrend@series[x] ~ x)$fitted.values, Index = x)
    })
    Partial <- rbindlist(Partial, fill = T)
    CreepyTrend@fitted <- Partial[ ,mean(Values, na.rm = T), by = Index]
    gc()
    return(CreepyTrend)
  }else(
      stop("Incorrect method of parallelization. Choose from 'cluster', 'simple', 'none'")
    )

}
