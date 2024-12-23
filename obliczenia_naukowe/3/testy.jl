# Felix Zielinski 272336

include("./metody.jl")
using .metody, Test

f(x) = x^2 - 16
g(x) = x^4 - 16
h(x) =  1/x - 0.05
i(x) = x^3 + 1
pf(x) = 2 * x
pg(x) = 4 * (x^3)
ph(x) = -x^(-2)
pi(x) = 3 * x^2
 
delta = 10.0^(-3.0)
epsilon = 10.0^(-3.0)
maxit = 64

error = 4
val = 1


@testset "mbisekcji_test" begin
    @test !mbisekcji(f, 2.0, 5.5, delta, epsilon)[error] 
    @test !mbisekcji(g, 2.0, 5.5, delta, epsilon)[error]
    @test !mbisekcji(h, 10.0, 25.0, delta, epsilon)[error]
    @test !mbisekcji(i, -2.0, 3.0, delta, epsilon)[error]

    @test isapprox(mbisekcji(f, 2.0, 5.5, delta, epsilon)[val], 4.0, atol = 0.01)
    @test isapprox(mbisekcji(g, 2.0, 5.5, delta, epsilon)[val], 2.0, atol = 0.01)
end

@testset "msiecznych_test" begin
    @test !msiecznych(f, 1.0, 5.0, delta, epsilon, maxit)[error]
    @test !msiecznych(g, 1.0, 5.0, delta, epsilon, maxit)[error]
    @test !msiecznych(h, 10.0, 25.0, delta, epsilon, maxit)[error]
    @test !msiecznych(i, 10.0, 0.8, delta, epsilon, maxit)[error]


    @test isapprox(msiecznych(f, 1.0, 5.0, delta, epsilon, maxit)[val], 4.0, atol = 0.01)
    @test isapprox(msiecznych(g, 1.0, 5.0, delta, epsilon, maxit)[val], 2.0, atol = 0.01)
end

@testset "mstycznych_test" begin
    @test mstycznych(f, pf, 6.0, delta, epsilon, maxit)[error] == 0
    @test mstycznych(g, pg, 6.0, delta, epsilon, maxit)[error] == 0
    @test mstycznych(h, ph, 6.0, delta, epsilon, maxit)[error] == 0
    @test mstycznych(i, pi, 0.8, delta, epsilon, maxit)[error] == 0

    @test isapprox(mstycznych(f, pf, 6.0, delta, epsilon, maxit)[val], 4.0, atol = 0.01)
    @test isapprox(mstycznych(g, pg, 6.0, delta, epsilon, maxit)[val], 2.0, atol = 0.01)
end

@testset "errors" begin
    @test mstycznych(i, pi, 0.8, delta, epsilon, 10)[error] == 1
    @test mbisekcji(i, 2.0, 3.0, delta, epsilon)[error]
end
