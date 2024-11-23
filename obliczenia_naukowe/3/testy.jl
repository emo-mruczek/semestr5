# Felix Zielinski 272336

include("./metody.jl")
using .metody, Test

f(x) = x^2 - 16
g(x) = x^4 - 16
pf(x) = 2*x
pg(x) = 4*(x^3)

delta = 10.0^-8.0
epsilon = 10.0^-8.0
maxit = 64

error = 4
val = 1

@testset "mbisekcji_test" begin
    @test !mbisekcji(f, 2.0, 5.5, delta, epsilon)[error] 
    @test !mbisekcji(g, 2.0, 5.5, delta, epsilon)[error]

    @test isapprox(mbisekcji(f, 2.0, 5.5, delta, epsilon)[val], 4.0, atol = 0.01)
    @test isapprox(mbisekcji(g, 2.0, 5.5, delta, epsilon)[val], 2.0, atol = 0.01)
end

@testset "msiecznych_test" begin
    @test !msiecznych(f, 1.0, 5.0, delta, epsilon, maxit)[error]
    @test !msiecznych(g, 1.0, 5.0, delta, epsilon, maxit)[error]

    @test isapprox(msiecznych(f, 1.0, 5.0, delta, epsilon, maxit)[val], 4.0, atol = 0.01)
    @test isapprox(msiecznych(g, 1.0, 5.0, delta, epsilon, maxit)[val], 2.0, atol = 0.01)
end

@testset "mstycznych_test" begin
    @test mstycznych(f, pf, 6.0, delta, epsilon, maxit)[error] == 0
    @test mstycznych(g, pg, 6.0, delta, epsilon, maxit)[error] == 0

    @test isapprox(mstycznych(f, pf, 6.0, delta, epsilon, maxit)[val], 4.0, atol = 0.01)
    @test isapprox(mstycznych(g, pg, 6.0, delta, epsilon, maxit)[val], 2.0, atol = 0.01)
end

