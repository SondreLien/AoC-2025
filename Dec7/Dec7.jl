# set working directory
cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

# PART 1

global numberOfSplits = 0

for i in 1:length(lines) - 1
    line = lines[i]
    indices = findall(isequal('|'), line)
    
    if (!isempty(indices))
        followingLine = collect(lines[i + 1])
        for index in indices
            if (lines[i + 1][index] == '.')   
                followingLine[index] = '|'
            end
        end
        
        lines[i + 1] = join(followingLine)
    end

    indices = findall(isequal('^'), line)

    if (isempty(indices))
        index = findfirst(isequal('S'), line)
        if (isnothing(index))
            continue
        end

        followingLine = collect(lines[i + 1])
        followingLine[index] = '|'
        lines[i + 1] = join(followingLine)
    end
    
    followingLine = collect(lines[i + 1])

    for index in indices
        if lines[i - 1][index] == '|'
            followingLine[index - 1] = '|'
            followingLine[index + 1] = '|'
            global numberOfSplits = numberOfSplits + 1
        end
    end
    
    lines[i + 1] = join(followingLine)
end

for line in lines
    println(line)
end

# PART 2

currentLine = length(lines)
beamIndices = findall(isequal('|'), lines[currentLine])

const GOAL = UInt8('S')
const SPLITTER = UInt8('^')
const BEAM = UInt8('|')

function recursiveFollowLine(_lines, cache, counter::Base.RefValue{Int}, lineLength, lineIndex, characterIndex)
    @inbounds begin
        # check if path is cached
        a = cache[lineIndex, characterIndex]
        if a != -1
            counter[] += a
            return
        end

        lineAbove = _lines[lineIndex - 1]

        if lineIndex - 1 == 1 && lineAbove[characterIndex] == GOAL
            counter[] += 1
            return
        end

        base = counter[]
        
        if (characterIndex > 1 && lineAbove[characterIndex - 1] == SPLITTER) 
            recursiveFollowLine(_lines, cache, counter, lineLength, lineIndex - 1, characterIndex - 1)
        end
        if (characterIndex < lineLength && lineAbove[characterIndex + 1] == SPLITTER)
            recursiveFollowLine(_lines, cache, counter, lineLength, lineIndex - 1, characterIndex + 1)
        end
        if (lineAbove[characterIndex] == BEAM)
            recursiveFollowLine(_lines, cache, counter, lineLength, lineIndex - 1, characterIndex)
        end

        # cache path
        cache[lineIndex, characterIndex] = counter[] - base
    end
end

println()

routeCounter = Ref(0)
fast_lines = [codeunits(line) for line in lines]
cache = fill(-1, length(fast_lines), length(fast_lines[1]))

for index in beamIndices
    recursiveFollowLine(fast_lines, cache, routeCounter, length(fast_lines[1]), currentLine, index)
    println("Destination index: $index - Total routes: $(routeCounter[])")
end

println()

println("Number of splits (Part 1): $numberOfSplits")
println("Number of routes (Part 2): $(routeCounter[])")