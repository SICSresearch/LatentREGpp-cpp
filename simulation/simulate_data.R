#rm(list=ls())  

#####    POLI-MULTI  ######


########ARGUMENTOS:

#size.cluster: tamaño de cada cluster de items (dim. teorica)
#dim.data: dimension de los datos, (dim. practica)
#sample.size: num de individuos
#ncatgs: numero de categorias por cada item

########DEVUELVE:

#1.  test 
#2.  parámetros con los que se generó, bajo la parámetrizacion
#en la que se distribuye la discriminacion, en el predictor lineal
#3. indices de cada cluster de items


#normal truncada y funcion que normaliza vectores:

source("/home/milder/Documents/workspace/MIRTcpp/simulation/rtnorm.r")


simulate.poly.multi=function(size.cluster=c(25,25,25,25),
                             dim.data=3,sample.size=1000,
                             ncatgs=rep(3,sum(size.cluster)), seed_data = 1273  ){
  
  #tamaño del test(num. de items)
  K=sum(size.cluster)
  
  #dimension teorica, numero de clusters
  num.cluster=length(size.cluster)
  
  #indices para especificar items por cada cluster
  ind2=cumsum(size.cluster)
  ind1=c(1,ind2[-length(ind2)]+1)
  
  #vectores directores principales
  set.seed(2)
  dir.beta.1=matrix(runif(dim.data^2,min=0.08,max=0.28),
                    nrow = dim.data,ncol = dim.data)
  
  if(num.cluster!=dim.data){
    dir.beta.2=rbind(dir.beta.1,
                     matrix(rep(1,dim.data*(num.cluster-dim.data)),ncol=dim.data))
    diag(dir.beta.2)=1
    dir.beta=normalize(dir.beta.2)
  }else{
    diag(dir.beta.1)=1
    dir.beta=normalize(dir.beta.1)
  }
  
  
  ##ruido, variacion respecto a los vectores directores principales
  noise <- seq(0.08, 0.25 ,length.out=num.cluster)
  
  ##betas, vectores directores de cada item
  betas.1 = matrix(NA,K,dim.data)
  
  # semilla para generar los vectores directores de cada ??tem.
  seed_beta <- 100L
  set.seed(seed_beta)
  
  #generando los vectores directores de cada item:
  for(i in 1:length(ind1)){
    betas.1[ind1[i]:ind2[i],]=
      matrix(dir.beta[i,], size.cluster[i],dim.data,byrow=TRUE)+matrix(runif(size.cluster[i]*dim.data,-noise[i],noise[i]), size.cluster[i],dim.data)
  }
  
  # replace  negative componentes
  
  betas.2=ifelse(betas.1<0,0,betas.1)
  betas=normalize(betas.2)
  
  
  ##se fijan d vectores directores al origen de la dimension de los datos
  #para resolver la falta de identificabilidad del modelo
  for(i in 1:dim.data){
    betas[ind1[i],i]=1 ; betas[ind1[i],-i]=0
  }
  
  
  ##se calculan los vectores directores principales "reales"
  dir_betas=matrix(NA,nrow=num.cluster,ncol=dim.data)
  
  for(i in 1:nrow(dir_betas)){
    dir_betas[i,]=abs(eigen(t(betas[ind1[i]:ind2[i],])%*%betas[ind1[i]:ind2[i],])$vectors)[,1]
  }
  
  
  #######################################################################
  # 2.item parameters
  #######################################################################
  
  # alpha params
  # seed for reproductibility
  seed_alpha <- 400L
  set.seed(seed_alpha)
  l_a=0.25
  u_a = Inf
  
  
  #se simulan las normas de los alphas
  norm.alphas<-rtnorm(K, mean = 0, sd = 1.0, lower = l_a,  upper = u_a)
  
  #se generan los alpha,(alpha=beta|alpha|)
  alphas = betas * matrix(norm.alphas, K, dim.data, byrow=FALSE)
  
  
  #se fijan d alphas para resolver la no identificabilidad.
  for(i in 1:dim.data){
    alphas[ind1[i],i]=1 ; alphas[ind1[i],-i]=0
  }
  
  
  ##########################!!!!!
  
  # umbrales*normas
  # seed for reproductibility
  seed_gamma <- 250L
  set.seed(seed_gamma)
  
  deltas=vector("list",length = K)
  umbrales=vector("list",length = K)
  
  ##generando deltas, las distancias entre umbrales 
  for(l in 1:K){
    deltas[[l]]=c(runif(1,-1.5,-1),rnorm((ncatgs[l]-2),0,0.4))
  }
  
  ##generando los umbrales
  umbrales=lapply(deltas,function(x)cumsum(c(x[1],exp(x[-1]))))
  
  ##distribuyendo la norma (hallando el d)
  Gamma=list()
  for(l in 1:K){
    Gamma[[l]]=-as.vector(umbrales[[l]])*norm.alphas[l]
  }
  
  
  ##no identificabilidad
  #for(i in 1:dim.data){
  # Gamma[[ind1[i]]][1]=0
  #  }
  
  
  if(length(Gamma[[ind1[1]]])!=1) Gamma[[ind1[1]]][2]=0
  if(length(Gamma[[ind1[2]]])!=1) Gamma[[ind1[2]]][2]=0
  
  
  #######################################################################
  # 3. latent traits
  #######################################################################
  # sample size
  
  seed.5 <-500L
  set.seed(seed.5)
  theta <- matrix(rnorm(sample.size*dim.data,0,1),sample.size,dim.data)
  # this line is to garantee the the covariance matrix is the identity
  theta <- theta %*% solve((chol(cov(theta))))
  theta.true <- theta
  
  
  #######################################################################
  # 3. test data
  #######################################################################
  
  ######################################
  #  3.1 probability
  #####################################
  
  ##pasteriscos:
  
  etas=list()
  thet.alpha=theta%*%t(alphas)
  for(j in 1:ncol(thet.alpha)){ 
    etas[[j]]=thet.alpha[,j]+
      matrix(Gamma[[j]],byrow=T,nrow=nrow(thet.alpha),ncol=length(Gamma[[j]]))
  }
  
  past.1=lapply(etas,function(x){1/(1+exp(-x))})
  past=lapply(past.1,function(x) cbind(1,x,0))
  probs=lapply(past,function(x) x[,-ncol(x)]-x[,-1])
  
  #lapply(probs,function(x)rowSums(x))
  
  #####################################
  #  3.2 Test data
  #####################################
  
  set.seed(seed_data)
  Y=matrix(NA,nrow=sample.size,ncol=K)
  for(i in 1:sample.size){
    for(j in 1:K){
      Y[i,j]=sample(1:ncatgs[j],1,prob = probs[[j]][i,])
    }
  }
  
  params.it=list()
  for(j in 1:length(umbrales))
  {params.it[[j]]=c(alphas[j,],Gamma[[j]])}
  
  
  retorno=list(data=Y,params.it=params.it,theta=theta,indclust1=ind1,indclust2=ind2)
  return(retorno)
}


#funcion que simula los datos en poli uni
simulate.poly.uni = function (n = 1000, nitems = 10, ncatgs = c(rep(3, 5), rep(4, 5)), model = "grm", seed_item = 1000,seed_data) 
{
  thetas = list()
  umbrales = list()
  disc=list()
  set.seed(seed_item)
  for ( i in 1:nitems ) {
    beta1 = runif(n = 1, min = -2, max = -1)
    deltas = runif(n = ncatgs[i] - 2, min = -0.4, 1)
    umbrales[[i]] = c(cumsum(c(beta1, exp(deltas))))
    alpha = runif(n = 1, min = 0.7, max = 2)
    thetas[[i]] = c(umbrales[[i]] * alpha, alpha)
    disc[[i]]=alpha
  }
  
  
  
  z <- rnorm(n)#Vector de trazos latentes segun la distribucion
  p <- length(thetas)#numero de items
  nk <- sapply(thetas, length) ##numero de categorias por item
  
  prob <- if (model == "grm") { #aca si entra
    thetas <- lapply(thetas, function(x) {
      n_x <- length(x)
      cbind(plogis(matrix(x[-n_x], n, n_x - 1, TRUE) - x[n_x] * z), 1)
    })
    lapply(thetas, function(x) {
      nc <- ncol(x)
      cbind(x[, 1], x[, 2:nc] - x[, 1:(nc - 1)])
    })
  }
  
  data <- matrix(0, n, p)
  set.seed(seed_data)
  for (j in 1:p) {
    ##Extrae las muestras con las probabilidades halladas anteriormente segun el modelo
    for (i in 1:n) data[i, j] <- sample(nk[j], 1, prob = prob[[j]][i, ])
  }
  
  d = umbrales
  for ( j in 1:p ) {
    d[[j]] = -1 * d[[j]] * disc[[j]]
  }
  
  retorno = list(data = data, params.it = mapply(function(x,y){c(x,y)},disc,d))
  return(retorno)
}



#### FUNCTION TO SIMULATE DATA ########

# It calls functions above 'simulate.poli.multi' and 'simulate.poli.uni'

simulate.data = function(size.cluster, dim.data, sample.size, ncatgs, folder, save = FALSE, replicas = 100, dicho = FALSE) {
  sims = list()
  for ( i in 1:replicas ) {
    sim = list()
    if ( dim.data > 1 )
      sim = simulate.poly.multi(sample.size = sample.size, size.cluster = size.cluster, dim.data = dim.data,
                                ncatgs = ncatgs, seed_data = i)  
    else 
      sim = simulate.poly.uni(n = sample.size, nitems = sum(size.cluster), ncatgs = ncatgs, seed_data = i)
    
    Y = list()
    if ( dicho == TRUE )
      Y = sim$data - 1
    else
      Y = sim$data
    sims[[i]] = sim
    if ( save == TRUE )
      write.table(Y, file = paste(c(folder, i,".csv"), collapse = ""), sep = ";",col.names = FALSE, row.names = FALSE)
  }
  
  
  longest = 0
  for ( i in 1:length(sims[[1]]$params.it) ) {
    if ( length((sims[[1]]$params.it)[[i]]) > longest )
      longest = length((sims[[1]]$params.it)[[i]])
  }
  
  params = matrix(NA, length(sims[[1]]$params.it), longest)
  
  for ( i in 1:length(sims[[1]]$params.it) ) {
    for ( j in 1:length((sims[[1]]$params.it)[[i]]) )
      params[i, j] = (sims[[1]]$params.it)[[i]][[j]]
  }
  
  write.table(params, file = paste(c(folder, "parameters.csv"), collapse = ""), sep = ";",col.names = FALSE, row.names = FALSE)
}


##################################################################################
##################################################################################
##################################################################################
#                                                                                #
#                                     1D                                         #
#                                                                                #
##################################################################################
##################################################################################
##################################################################################

# ESCENARIO 1
# k = 1000
################# 1000 x 10 ###########################

simulate.data(size.cluster = c(5, 5), dim.data = 1, 
              sample.size = 1000, ncatgs = c(rep(2, 5), rep(3, 5)),
              folder = "IRTpp/datasets/1D/poly/escenario1/1D-poly-1000x10-", save = TRUE)
# ESCENARIO 2
# k = 1000
################# 2000 x 10 ###########################

simulate.data(size.cluster = c(5, 5), dim.data = 1, 
              sample.size = 2000, ncatgs = c(rep(2, 5), rep(3, 5)),
              folder = "IRTpp/datasets/1D/poly/escenario2/1D-poly-2000x10-", save = TRUE)
# ESCENARIO 3
# k = 1000
################# 5000 x 20 ###########################

simulate.data(size.cluster = c(10, 10), dim.data = 1, 
              sample.size = 5000, ncatgs = c(rep(2, 10), rep(3, 10)),
              folder = "IRTpp/datasets/1D/poly/escenario3/1D-poly-5000x20-", save = TRUE)
# ESCENARIO 4
# k = 1000
################# 10000 x 20 ###########################

simulate.data(size.cluster = c(10, 10), dim.data = 1, 
              sample.size = 10000, ncatgs = c(rep(2, 10), rep(3, 10)),
              folder = "IRTpp/datasets/1D/poly/escenario4/1D-poly-10000x20-", save = TRUE)
# ESCENARIO 5
# k = 1000
################# 20000 x 20 ###########################

simulate.data(size.cluster = c(10, 10), dim.data = 1, 
              sample.size = 20000, ncatgs = c(rep(2, 10), rep(3, 10)),
              folder = "IRTpp/datasets/1D/poly/escenario5/1D-poly-20000x20-", save = TRUE)



##################################################################################
##################################################################################
##################################################################################
#                                                                                #
#                                     2D                                         #
#                                                                                #
##################################################################################
##################################################################################
##################################################################################

# ESCENARIO 1
# k = 1000
################# 1000 x 50 ###########################

simulate.data(size.cluster = c(25, 25), dim.data = 2, 
              sample.size = 1000, ncatgs = c(rep(2, 25), rep(3, 25)),
              folder = "IRTpp/datasets/2D/poly/escenario1/2D-poly-1000x50-", save = TRUE)

# ESCENARIO 2
# k = 1000
################# 2000 x 50 ###########################

simulate.data(size.cluster = c(25, 25), dim.data = 2, 
              sample.size = 2000, ncatgs = c(rep(3, 25), rep(4, 25)),
              folder = "IRTpp/datasets/2D/poly/escenario2/2D-poly-2000x50-", save = TRUE)

# ESCENARIO 3
# k = 1000
################# 5000 x 100 ###########################

simulate.data(size.cluster = c(50, 50), dim.data = 2, 
              sample.size = 5000, ncatgs = c(rep(4, 50), rep(5, 50)),
              folder = "IRTpp/datasets/2D/poly/escenario3/2D-poly-5000x100-", save = TRUE)


# ESCENARIO 4
# k = 1000
################# 10000 x 100 ###########################

simulate.data(size.cluster = c(50, 50), dim.data = 2, 
              sample.size = 10000, ncatgs = c(rep(3, 50), rep(5, 50)),
              folder = "IRTpp/datasets/2D/poly/escenario4/2D-poly-10000x100-", save = TRUE)

# ESCENARIO 5
# k = 1000
################# 20000 x 100 ###########################

simulate.data(size.cluster = c(50, 50), dim.data = 2, 
              sample.size = 20000, ncatgs = c(rep(3, 50), rep(5, 50)),
              folder = "IRTpp/datasets/2D/poly/escenario5/2D-poly-20000x100-", save = TRUE)

#
#
#
#



################# 1000 x 100 ###########################

simulate.data(size.cluster = c(20, 20, 20, 20, 20), dim.data = 5, 
              sample.size = 1000, ncatgs = c(rep(2, 100)),
              folder = "IRTpp/datasets/5D-dicho-1000x100-", save = TRUE, replicas = 1)

##################################################################################
##################################################################################
##################################################################################
#                                                                                #
#                                     6D                                         #
#                                 Polytomous                                     #
##################################################################################
##################################################################################
##################################################################################  


simulate.data(size.cluster = c(25, 25, 25, 25), dim.data = 4, 
              sample.size = 1000, ncatgs = c(rep(3, 100)),
              folder = "/home/milder/Documents/workspace/MIRTcpp/datasets/4D-poly-1000x100-", save = TRUE, replicas = 1)





##################################################################################
##################################################################################
##################################################################################
#                                                                                #
#                                     6D                                         #
#                                 Dichotomous                                    #
##################################################################################
##################################################################################
##################################################################################                           


simulate.data(size.cluster = c(10, 10, 10, 10, 10, 10), dim.data = 6, 
              sample.size = 1000, ncatgs = c(rep(2, 60)),
              folder = "/home/milder/Documents/workspace/MIRTcpp/datasets/6D-dicho-1000x60-", save = TRUE, replicas = 1, dicho = TRUE)


##################################################################################
#                                                                                #
#                                     6D                                         #
#                                 Polytomous                                     #
##################################################################################
##################################################################################
##################################################################################     


simulate.data(size.cluster = c(10, 10, 10, 10, 10, 10), dim.data = 6, 
              sample.size = 1000, ncatgs = c(rep(3, 60)),
              folder = "/home/milder/Documents/workspace/MIRTcpp/datasets/6D-poly-1000x60-", save = TRUE, replicas = 1)

simulate.data(size.cluster = c(10, 10, 10, 10, 10, 10), dim.data = 6, 
              sample.size = 1000, ncatgs = c(rep(3, 60)),
              folder = "/home/milder/Documents/workspace/MIRTcpp/datasets/6D-poly-1000x60-", save = TRUE, replicas = 1)










sim = simulate.poly.multi(sample.size = 5000, size.cluster = c(20, 20), dim.data = 2,
                          ncatgs = rep(2, 40), seed_data = 767)

sim = simulate.poly.uni(n = 5000, nitems = c(40), ncatgs = rep(2, 40), seed_data = 457)

sim$params.it
sim$data = sim$data - 1
sim$theta

write.table(file = "/home/milder/Documents/workspace/MIRTcpp/datasets/1D-5000x40.csv", sep = ";", x = sim$data, row.names = FALSE, col.names = FALSE)
