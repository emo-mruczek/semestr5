using Base.Threads

# bitstring(n) A string giving the literal bit representation of a primitive type. 
function is_evenly(step, b::Float64, e::Float64)
    x = b
    dif = Float64[]

    while x + step < e
        next = x + step
        push!(dif, next - x)
        x = next
        println(x, " ")
    end

    return all(d -> d == step, dif)
end

function is_evenly_threads(step, b::Float64, e::Float64)
    threads = nthreads()
    range = ( e - b ) / threads
    results = Vector{Bool}(undef, threads)

    @threads for i in 1:threads
        start = b + ( i - 1 ) * range
        stop = ( i == threads ? e : start + range )
        results[i] = is_evenly(step, start, stop)
    end

    return all(results)
end


println("Are they equal? ", is_evenly_threads(2.0^(-52), 1.0, 2.0))
