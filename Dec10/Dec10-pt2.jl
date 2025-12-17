# set working directory

cd(@__DIR__)

include("InitData.jl")

using JuMP
using HiGHS

totalButtonPresses = 0

for idx in eachindex(buttons)
    # Using linear algebra to solve problem
    # A * x = b where
    # - A is the button matrix - each row represents which button is being pressed (value 1)
    # - x is the number of presses vector
    # - b is the resulting joltage vector
    
    # Define matrix
    A = zeros(Int, length(joltages[idx]), length(buttons[idx]))

    for (i, btn) in enumerate(buttons[idx])
        for j in btn
            A[j + 1, i] = 1
        end
    end

    b = joltages[idx]

    # display(A)
    # display(b)

    model = Model(HiGHS.Optimizer)
    set_silent(model)

    @variable(model, x[1:length(buttons[idx])] >= 0, Int) # Define variable - Each occurence of x is bigger than 0 and is an integer value
    @constraint(model, A * x .== b) # Ax = b - use .== to constraint per entry (since A*x is vector and b is vector)
    @constraint(model, x .<= 200) # Per button cannot be pressed more than 200 times
    @objective(model, Min, sum(x)) # Minimize the sum of the x-vector

    optimize!(model)

    minPresses = sum(value.(x))
    println("Minimum button presses: $(sum(value.(x)))")
    global totalButtonPresses += minPresses

end

println()
println("PART 2: Total number of button presses: $totalButtonPresses")