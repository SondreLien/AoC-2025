using Memoization

# set working directory

cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

# format data

_deviceMap = Dict{Int, Vector{String}}()
deviceIdMap = Dict{String, Int}()

for i in eachindex(lines)
    line = lines[i]
    splt = split(line, ':')
    key = splt[1]
    devices = split(splt[2], ' ')[2:end]
    _deviceMap[i] = devices
    deviceIdMap[key] = i
end

deviceMap = Dict{Int, Vector{Int}}()
for (key, value) in _deviceMap
    devices = Vector{Int}()
    for device in value
        if !haskey(deviceIdMap, device)
            deviceIdMap[device] = length(deviceIdMap) + 1
        end
        push!(devices, deviceIdMap[device])
    end
    deviceMap[key] = devices
end

if !(haskey(deviceIdMap, "out"))
    deviceIdMap["out"] = length(deviceIdMap) + 1
    deviceMap[length(deviceMap) + 1] = deviceIdMap["out"]
end
if !(haskey(deviceIdMap, "dac"))
    deviceIdMap["dac"] = length(deviceIdMap) + 1
    deviceMap[length(deviceMap) + 1] = []
end
if !(haskey(deviceIdMap, "fft"))
    deviceIdMap["fft"] = length(deviceIdMap) + 1
    deviceMap[length(deviceMap) + 1] = []
end
if !(haskey(deviceIdMap, "svr"))
    deviceIdMap["svr"] = length(deviceIdMap) + 1
    deviceMap[length(deviceMap) + 1] = []
end
if !(haskey(deviceIdMap, "you"))
    deviceIdMap["you"] = length(deviceIdMap) + 1
    deviceMap[length(deviceMap) + 1] = []
end

for (key, value) in deviceIdMap
    println("Key: $key, Mapped value: $value")
end

for (key, value) in deviceMap
    println("Key: $key, value: $value")
end

const YOU = deviceIdMap["you"]
const OUT = deviceIdMap["out"]
const DAC = deviceIdMap["dac"]
const FFT = deviceIdMap["fft"]
const SVR = deviceIdMap["svr"]

println()

@memoize function recursiveFollow(deviceToVisit::Int, isPart2::Bool, dacPassed::Bool, fftPassed::Bool)    
    _newDacPassed = dacPassed
    _newfftPassed = fftPassed

    if isPart2 
        if deviceToVisit == DAC
            _newDacPassed = true
        elseif deviceToVisit == FFT
            _newfftPassed = true
        elseif deviceToVisit == OUT 
            if _newDacPassed && _newfftPassed
                return 1
            else
                return 0
            end 
        end
    elseif deviceToVisit == OUT
        return 1
    end

    if visited[deviceToVisit]
        return 0
    end 
    if !haskey(deviceMap, deviceToVisit) 
        return 0
    end

    visited[deviceToVisit] = true
    
    totalpaths = 0

    for connectedDevice in deviceMap[deviceToVisit]
        totalpaths += recursiveFollow(connectedDevice, isPart2, _newDacPassed, _newfftPassed)
    end

    visited[deviceToVisit] = false

    return totalpaths
end

println()
println("Calculating part 1...")
visited = Vector{Bool}(falses(length(deviceIdMap)))
numberOfPaths = recursiveFollow(YOU, false, false, false)
println()

println("Calculating part 2...")
visited = Vector{Bool}(falses(length(deviceIdMap)))
numberOfPaths2 = recursiveFollow(SVR, true, false, false)
Memoization.empty_cache!(recursiveFollow)
println()

println("PART 1: $(numberOfPaths)")
println("PART 2: $(numberOfPaths2)")