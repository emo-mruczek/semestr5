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

# funkcja gauss
# parametry: 
#   A - macierz Float64
#   size - wielkość macierzy
#
# funkcja zwraca Float64 -> błąd względny przy metodzie gaussa


function gauss(A::Matrix{Float64}, size::Int64)::Float64
    x::Vector{Float64} = ones(Float64, size)
    b::Vector{Float64} = A * x;
    res::Vector{Float64} = A \ b
    ret::Float64 = norm(res - x) / norm(x)

    return ret
end

# funkcja inv
# parametry: 
#   A - macierz Float64
#   size - wielkość macierzy
#
# funkcja zwraca Float64 -> błąd względny przy metodzie inwersji


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
