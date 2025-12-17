using DataStructures

# set working directory

cd(@__DIR__)

include("InitData.jl")

function recursivePressButton(currentValue::Base.RefValue{Int}, lowestCombination::Base.RefValue{Int}, buttonsPressed::Vector{Int}, currentButton::Int, availableButtons::Vector{Int}, targetValue::Int)
    
    currentValue[] = xor(currentValue[], currentButton)
    push!(buttonsPressed, currentButton)
    
    if (length(buttonsPressed) > lowestCombination[] || length(buttonsPressed) >= length(availableButtons))
        return
    end

    if (currentValue[] == targetValue && length(buttonsPressed) > 0)
        if (length(buttonsPressed) < lowestCombination[])
            lowestCombination[] = length(buttonsPressed)
        end
        return
    end
    
    for i in eachindex(availableButtons)
        nextButton = availableButtons[i]
        if nextButton == currentButton
            continue
        end
        cpy_currentValue = Ref(currentValue[])
        cpy_buttonsPressed = copy(buttonsPressed)
        recursivePressButton(cpy_currentValue, lowestCombination, cpy_buttonsPressed, nextButton, availableButtons, targetValue)
    end
end

sum_part_1 = 0
for i in eachindex(lightTemplates)
    lowestCombination = Ref(100)
    target = lightTemplates[i]
    for button in buttons_dec[i]
        if button == 17
            breakme = true
        end
        currentValue = Ref(0)
        recursivePressButton(currentValue, lowestCombination, Vector{Int}(), button, buttons_dec[i], target)
    end
    println("Lowest combination for $i: $(lowestCombination[])")
    global sum_part_1 += lowestCombination[]
end

println()
println("SUM (Part 1): $sum_part_1")