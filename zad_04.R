getwd()
setwd("D:/162253")
z <- read.table("imports-85.data", sep = ",", na.strings = "?")
str(z)

names <- c("symboling","normalized-losses", "make", "fuel-type", "aspiration", "num-of-doors", "body-style", "drive-wheels", "engine-location",
           "wheel-base", "length", "width", "height", "curb-weight", "engine-type", "num-of-cylinders", "engine-size", "fuel-system", "bore", 
           "stroke", "compression-ratio", "horsepower", "peak-rpm", "city-mpg", "highway-mpg", "price")
names(z) <- names
temp <- factor(z[[1]], level=3:3)
temp
str(temp)
tempz <- z[[2]]
meanz <- mean(tempz, na.rm = TRUE)
meanz
tempz[is.na(tempz)] <- meanz
z[[2]] <- tempz
str(z)

factorize <- factor(z[[3]])
str(z)
z[[3]] <- factorize
str(z)

factorize <- factor(z[[4]])
str(z)
z[[4]] <- factorize
str(z)

factorize <- factor(z[[5]])
z[[5]] <- factorize

factorize <- factor(z[[6]])
zm <- table(factorize)
which.max(zm)
tmp <- names(zm[which.max(zm)])
factorize[is.na(factorize)] <- tmp
str(factorize)
z[[6]] <- factorize
str(z)

factorize <- factor(z[[7]])
str(factorize)
z[[7]] <- factorize

factorize <- factor(z[[8]])
str(factorize)
z[[8]] <- factorize

factorize <- factor(z[[9]])
str(factorize)
z[[9]] <- factorize

str(z)

factorize <- factor(z[[15]])
str(factorize)
z[[15]] <- factorize

factorize <- factor(z[[16]])
str(factorize)
z[[16]] <- factorize

str(z)

factorize <- factor(z[[17]])
str(factorize)
z[[17]] <- factorize

factorize <- factor(z[[18]])
str(factorize)
z[[18]] <- factorize

factorize <- is.na(z[[19]])
str(factorize)
factorize <- !is.na(z[[19]])
str(factorize)
x <- z[factorize, ]
str(x)
z <- x

str(z)

factorize <- is.na(z[[22]])
x <- z[[22]]
m <- mean(x[[22]], na.rm = TRUE)
m
x[is.na(x)] <- m
x
z[[22]] <- x


m <- median(z[[23]], na.rm = TRUE)
m
x[is.na(x)] <- m
x
na.fail(x)
z[[23]] <- x


factorize <- is.na(z[[26]])
factorize <- !is.na(z[[26]])
str(factorize)
x <- z[factorize, ]
str(x)
z <- x
na.fail(z)





#Zadania


