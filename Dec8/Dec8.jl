using DataStructures

# set working directory
cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

_junctions = [ (-1, -1, -1) for _ in 1:length(lines) ]

for i in eachindex(lines)
    line = lines[i]
    coords = split(line, ",")

    _junctions[i] = (parse(Int, coords[1]), parse(Int, coords[2]), parse(Int, coords[3]))
end

comparedJunctions = Vector{NTuple{3, Int}}()
junctionDistance = Vector{Float64}()
_junctions2 = Vector{NTuple{3, Int}}()

for i in eachindex(_junctions)
    junction = _junctions[i]
    
    for j in eachindex(_junctions)
        if (i == j)
            continue
        end
        nextJunction = _junctions[j]
        distance = sqrt((nextJunction[1] - junction[1])^2 + (nextJunction[2] - junction[2])^2 + (nextJunction[3] - junction[3])^2)

        push!(_junctions2, junction)
        push!(comparedJunctions, nextJunction)
        push!(junctionDistance, distance)
    end
end

# Sort by distance
idx = sortperm(junctionDistance)
shortestDistance_sorted = junctionDistance[idx]
closestJunctions_sorted = comparedJunctions[idx]
junctions_sorted = _junctions2[idx]

println()

connectionMap = Dict{NTuple{3,Int}, Set{NTuple{3,Int}}}()
connectionsMade = 0

function addToConnectionMap!(map::Dict{NTuple{3,Int}, Set{NTuple{3,Int}}}, key1::NTuple{3,Int}, key2::NTuple{3, Int})
    println("Connecting $key1 and $key2")

    if haskey(map, key1)
        push!(map[key1], key2)
    else
        map[key1] = Set([key2]) 
    end
    if haskey(map, key2)
        push!(map[key2], key1)
    else
        map[key2] = Set([key1]) 
    end
end

gridMap = Dict{Int, Set{NTuple{3, Int}}}()
revGridMap = Dict{NTuple{3, Int}, Int}()

gridCounter = 0
lastJunctions = [(-1, -1, -1), (-1, -1, -1)]
println()

for i in eachindex(junctions_sorted)
    junction = junctions_sorted[i]
    closestJunction = closestJunctions_sorted[i]

    if connectionsMade <= 1000

        # Avoid duplicate connections
        if haskey(connectionMap, junction)
            if closestJunction in connectionMap[junction]
                println("Connection between $junction and $closestJunction already exists")
                continue
            end
        end

        addToConnectionMap!(connectionMap, junction, closestJunction)
        global connectionsMade += 1
    end

    gridIndex = get(revGridMap, junction, -1)
    gridIndexClosest = get(revGridMap, closestJunction, -1)

    if (gridIndex == -1 && gridIndexClosest == -1)
        global gridCounter += 1
        revGridMap[junction] = gridCounter
        revGridMap[closestJunction] = gridCounter
        gridMap[gridCounter] = Set{NTuple{3, Int}}()
        push!(gridMap[gridCounter], junction)
        push!(gridMap[gridCounter], closestJunction)
    elseif gridIndex == -1 && gridIndexClosest != -1
        revGridMap[junction] = gridIndexClosest
        push!(gridMap[gridIndexClosest], junction)
    elseif gridIndex != -1 && gridIndexClosest == -1
        revGridMap[closestJunction] = gridIndex
        push!(gridMap[gridIndex], junction)
    elseif gridIndex != gridIndexClosest
        # Use gridIndex - just for shits and giggles
        for value in values(gridMap[gridIndexClosest])
            push!(gridMap[gridIndex], value)
        end

        delete!(gridMap, gridIndexClosest)

        for (key,value) in revGridMap
            if (value == gridIndexClosest)
                revGridMap[key] = gridIndex
            end
        end
    end  

    if (connectionsMade >= 1000)
        perc = round(i / length(junctions_sorted) * 100)
        print("\r[$perc%]\tCurrent number of grids: $(length(gridMap))")
    end
    
    if length(gridMap) == 1 && length(revGridMap) >= length(_junctions)
        global lastJunctions[1] = junction
        global lastJunctions[2] = closestJunction
        println()
        println("Last connected junction boxes: $junction and $closestJunction")
        break
    end
end

function getGridElementsRecursive(junctionBoxes::Set{NTuple{3,Int}}, currentKey::NTuple{3,Int}, conMap::Dict{NTuple{3,Int}, Set{NTuple{3,Int}}})
    value = conMap[currentKey]
    for entry in value
        if !(entry in junctionBoxes)
            push!(junctionBoxes, entry)
            getGridElementsRecursive(junctionBoxes, entry, conMap)
        end
    end
end

println()

gridIndex = 1
junctionBoxes = Dict{Int, Set{NTuple{3,Int}}}()
while length(connectionMap) > 0
    junctionBoxesInGrid = Set{NTuple{3,Int}}()
    startkey = first(keys(connectionMap))

    Base.invokelatest(getGridElementsRecursive, junctionBoxesInGrid, startkey, connectionMap)
    
    junctionBoxes[gridIndex] = junctionBoxesInGrid
    global gridIndex += 1
    
    for junctionBox in junctionBoxesInGrid
        #println("Deleting junctionbox: $(junctionBox)")
        delete!(connectionMap, junctionBox)
    end
end

println()

# for (key, value) in junctionBoxes
#     println("Grid: $key, Number of junction boxes: $(length(value))")
# end

highestVals = [0, 0, 0]
for value in values(junctionBoxes)
    if length(value) > highestVals[1]
        highestVals[3] = highestVals[2]
        highestVals[2] = highestVals[1]
        highestVals[1] = length(value)
    elseif length(value) > highestVals[2]
        highestVals[3] = highestVals[2]
        highestVals[2] = length(value)
    elseif length(value) > highestVals[3]
        highestVals[3] = length(value)
    end
end

product = 1
for value in highestVals
    global product *= value
end

product2 = lastJunctions[1][1] * lastJunctions[2][1]

println("Product (PART 1): $product")
println("Product (PART 2): $product2")