# Felix Zieliński 272336

using LinearAlgebra

function hilb(n::Int)
# Function generates the Hilbert matrix  A of size n,
#  A (i, j) = 1 / (i + j - 1)
# Inputs:
#	n: size of matrix A, n>=1
#
#
# Usage: hilb(10)
#
# Pawel Zielinski
        if n < 1
         error("size n should be >= 1")
        end
        return [1 / (i + j - 1) for i in 1:n, j in 1:n]
end


function matcond(n::Int, c::Float64)
# Function generates a random square matrix A of size n with
# a given condition number c.
# Inputs:
#	n: size of matrix A, n>1
#	c: condition of matrix A, c>= 1.0
#
# Usage: matcond(10, 100.0)
#
# Pawel Zielinski
        if n < 2
         error("size n should be > 1")
        end
        if c< 1.0
         error("condition number  c of a matrix  should be >= 1.0")
        end
        (U,S,V)=svd(rand(n,n))
        return U*diagm(0 =>[LinRange(1.0,c,n);])*V'
end

# my functions
# im repeating myself there i know

# function inv
# params: 
#   A - matrix Float64
#   size - size of the matrix
#
# function returns Float64 -> relative error for gauss method

function gauss(A::Matrix{Float64}, size::Int64)::Float64
    x::Vector{Float64} = ones(Float64, size)
    b::Vector{Float64} = A * x;
    res::Vector{Float64} = A \ b
    ret::Float64 = norm(res - x) / norm(x)

    return ret
end

# function inv
# params: 
#   A - matrix Float64
#   size - size of the matrix
#
# function returns Float64 -> relative error for inversion method


function inversion(A::Matrix{Float64}, size::Int64)::Float64
    x::Vector{Float64} = ones(Float64, size)
    b::Vector{Float64} = A * x;
    res::Vector{Float64} = inv(A) * b
    ret::Float64 = norm(res - x) / norm(x)

    return ret
end

println("Tests for Hilbers, when n = {1, 2, ..., 20}: n --- condition --- rank --- gauss error --- inv error\n")

hil_range::Int64 = 20

for n::Int64 in 1:hil_range
    A::Matrix{Float64} = hilb(n) # println(typeof(A))
    println(n, " --- ", cond(A), " --- ", rank(A), " --- ", gauss(A, n), " --- ", inversion(A, n))
end

println("Tests for random matrix, when n = {5, 10, 20} and c = {1, 10, 10^3, 10^7, 10^12, 10^16}:")
println("n --- c --- condition --- rank --- gauss error -- inv error\n")

gauss_range::Vector{Int64} = [5, 10, 20]
gauss_c::Vector{Int64} = [0, 1, 3, 7, 12, 16]

for n::Int64 in gauss_range
    for c::Int64 in gauss_c
        A::Matrix{Float64} = matcond(n, 10.0^c)
        println(n, " --- ", c, " --- ", cond(A), " --- ", rank(A), " --- ", gauss(A, n), " --- ", inversion(A, n))
    end
end
