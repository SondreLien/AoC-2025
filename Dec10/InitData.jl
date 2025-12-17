# set working directory

cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

_lightTemplates = Vector{String}()
_buttons = Vector{Vector{String}}()
_joltages = Vector{String}()

for line in lines
    lights = match(Regex(raw"\[(.*?)\]"), String(line))
    push!(_lightTemplates, lights.captures[1])
    
    btns = Vector{String}()
    for match in eachmatch(Regex(raw"\((.*?)\)"), String(line))
        push!(btns, match.captures[1])
    end
    push!(_buttons, btns)
    
    jolt = match(Regex(raw"\{(.*?)\}"), String(line))
    push!(_joltages, jolt.captures[1])
end

for i in eachindex(_lightTemplates)
    println("Lights: $(_lightTemplates[i]), buttons: $(_buttons[i]), joltages: $(_joltages[i])")
end

lightTemplates = Vector{Int}()
buttons = Vector{Vector{Vector{Int}}}()
buttons_dec = Vector{Vector{Int}}()
joltages = Vector{Vector{Int}}()

for i in eachindex(_lightTemplates)
    # Format light template to decimal
    decimal = 0
    for j in length(_lightTemplates[i]):-1:1
        char = _lightTemplates[i][j]
        decimal = decimal << 1
        decimal = decimal + Int(char == '#')
    end
    push!(lightTemplates, decimal)

    # Format buttons to integer vectors
    btnCollection = Vector{Vector{Int}}()
    for btn in _buttons[i]
        ids = Vector{Int}()
        for id_split in split(btn, ',')
            push!(ids, parse(Int, id_split))
        end
        push!(btnCollection, ids)
    end 
    push!(buttons, btnCollection)

    # Format buttons to decimal values
    btnDecCollection = Vector{Int}()
    for btns in btnCollection
        decimal = 0
        for indicator in btns
            decimal = decimal | (1 << indicator)
        end
        push!(btnDecCollection, decimal)
    end
    push!(buttons_dec, btnDecCollection)

    # Format joltages to single decimal
    jolts = Vector{Int}()
    for jlt in split(_joltages[i], ',')
        push!(jolts, parse(Int, jlt))
    end
    push!(joltages, jolts)
end

for i in eachindex(lightTemplates)
    println("Lights: $(lightTemplates[i]), buttons: $(buttons[i]), buttons (dec): $(buttons_dec[i]) joltages: $(joltages[i])")
end
println()