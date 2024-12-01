# Felix Zielinski 272336

include("./metody.jl")
using .metody, Test

@testset "ilorazyRoznicowe test" begin
    @test isapprox(ilorazyRoznicowe([1.0, 3.0, 4.0, 5.0], [4.0, -2.0, 10.0, 16.0]), [4.0, -3.0, 5.0, -2.0], rtol=1e-5)
    @test isapprox(ilorazyRoznicowe([3.0, 1.0, 5.0, 6.0], [1.0, -3.0, 2.0, 4.0]), [1.0, 2.0, -3.0/8.0, 7.0/40.0], rtol=1e-5)
    @test isapprox(ilorazyRoznicowe([-1.0, 0.0, 1.0, 2.0, 3.0], [2.0, 1.0, 2.0, -7.0, 10.0]),[2.0, -1.0, 1.0, -2.0, 2.0], rtol=1e-5) 
end


@testset "ilorazyRoznicowe test" begin
    @test isapprox(ilorazyRoznicowe([1.0, 3.1, 4.2, 5.0], [4.5, -1.8, 9.9, 15.7]), [4.5, -3.15, 4.75, -2.05], rtol=1e-5)
    @test isapprox(ilorazyRoznicowe([2.9, 1.1, 5.0, 6.2], [1.2, -2.8, 2.5, 4.1]), [1.2, 1.95, -0.35, 0.175], rtol=1e-5)
    @test isapprox(ilorazyRoznicowe([-1.2, 0.0, 1.3, 2.1, 3.0], [2.1, 1.2, 1.8, -6.8, 9.5]), [2.1, -0.9, 1.15, -1.95, 2.3], rtol=1e-5)
end
