# library(future)
# plan(multiprocess)
#
# x %<-% {
#   for(i in 1:10000){
#     d <- data.frame(y = rnorm(10000), x1 = rnorm(10000), x2 = runif(10000), x3 = runif(10000))
#     l <- lm(y ~., data = d)
#   }
#   l
# }
#
#
#
# y %<-% {
#   for(i in 1:10000){
#     d <- data.frame(y = rnorm(10000), x1 = rnorm(10000), x2 = runif(10000), x3 = runif(10000))
#     l <- lm(y ~., data = d)
#   }
#   l
# }
#
#
# w <- 1:3
#
# library(purrr)
#
# res <- map(w, function(p){
#   x %<-% {
#     for(i in 1:(100000/p)){
#       d <- data.frame(y = rnorm(10000), x1 = rnorm(10000), x2 = runif(10000), x3 = runif(10000))
#       l <- lm(y ~., data = d)
#     }
#     list(l, p)
#   }
# })
#
# res[[3]]$envir$x
