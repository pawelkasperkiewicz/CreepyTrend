library(tidyverse)
library(CreepyTrend)
library(parallel)

data <- fread("~/Pulpit/Data_temperature.csv")
data <- data[V4 == "12:00:00", .(Data_, V3)]
setnames(data, c("Data_", "V3"), c("Temp", "Date"))
data[, Date := lubridate::ymd(Date)]

data[Date > "2015-01-01"] %>% ggplot(aes(Date, Temp)) + geom_line(aes(group = 1))


data2 <- copy(data)
data2 <- copy(rbindlist(map(1:30, function(x) data)))


data2 <- copy(data[Date > "2015-01-01"])


Model <- CreepyTrend$new(x = data2$Temp)

start <- Sys.time()
Model$fit(l = 100)
stop <- Sys.time()
stop - start

Model$smoothed

data2 %>% ggplot(aes(Date, Temp)) + geom_line() + geom_line(y = Model$smoothed$y)


Model2 <- CreepyTrend(series = data2$Temp, k = 200)
