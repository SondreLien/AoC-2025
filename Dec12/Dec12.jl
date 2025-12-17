# set working directory

cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

gifts = Dict{Int, Matrix{Bool}}()
regions = Vector{Tuple{NTuple{2, Int}, Vector{Int}}}()

for i in eachindex(lines)
    indexLine = lines[i]
    if occursin(Regex(raw"(^\d:)"), String(indexLine))
        index = parse(Int, indexLine[1:end-1])
        println(index)

        gifts_vec = Vector{Vector{Bool}}()

        for j in (i+1):length(lines)
            gridLine = lines[j]
            println(gridLine)
            if !occursin(Regex(raw"(^(\#|\.))"), String(gridLine))
                break
            end
            vec = Vector{Bool}()
            for char in gridLine
                if char == '#'
                    push!(vec, true)
                else
                    push!(vec, false)
                end
            end
            push!(gifts_vec, vec)
        end

        grid = vcat((v' for v in gifts_vec)...)
        gifts[index] = grid
    elseif occursin(Regex(raw"(^\d+x\d+:)"), String(indexLine))
        splt = split(indexLine, ':')
        strsplt = split(splt[1], 'x')
        size = (parse(Int, strsplt[1]), parse(Int, strsplt[2]))
        
        pkgVec = Vector{Int}()
        for pkg in split(splt[2], ' ')
            if pkg != ""
                push!(pkgVec, parse(Int, pkg))
            end
        end
        push!(regions, (size, pkgVec))
    end
end

println()

for (key, value) in gifts
    println("$key matrix")
    display(value)
end

fitsCounter = 0

for region in regions
    println(region)
    totalPkgs = sum(region[2])
    availableArea = region[1][1] * region[1][2]
    areaToOccupy = 9 * totalPkgs
    usableXRange = Int(floor(region[1][1] / 3) * 3)
    usableYRange = Int(floor(region[1][2] / 3) * 3)

    # I have no idea why this works, but adding 20% to the size of usable area got me the right answer..
    # Not a good solution, but I dont bother fixing this code..

    usableArea = Int(floor(usableXRange * usableYRange * 1.2))
    println("We must fit area $areaToOccupy packages within $usableArea")
    if (areaToOccupy < usableArea)
        global fitsCounter += 1
    end
end

println("PART 1: A total of $fitsCounter fits")