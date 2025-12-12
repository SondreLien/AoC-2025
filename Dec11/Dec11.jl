# set working directory

cd(@__DIR__)

# import file

InputData = read("TestData.txt", String)
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
    deviceMap[length(deviceMap) + 1] = []
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

function recursiveFollow(devicesVisited::Vector{Bool}, deviceToVisit::Int, devices::Dict{Int, Vector{Int}}, isPart2::Bool = false)    
    if devicesVisited[deviceToVisit] || !haskey(devices, deviceToVisit)
        return 0
    end

    if deviceToVisit == OUT
        if !isPart2 || (devicesVisited[DAC] && devicesVisited[FFT])
            return 1
        else
            return 0
        end
    end

    devicesVisited[deviceToVisit] = true
    
    totalpaths = 0

    for connectedDevice in devices[deviceToVisit]
        totalpaths += recursiveFollow(devicesVisited, connectedDevice, devices, isPart2)
    end

    devicesVisited[deviceToVisit] = false

    return totalpaths
end

visited = Vector{Bool}(falses(length(deviceIdMap)))
println()
println("Calculating part 1...")
numberOfPaths = recursiveFollow(visited, YOU, deviceMap)
println()

visited = Vector{Bool}(falses(length(deviceIdMap)))
println("Calculating part 2...")
numberOfPaths2 = recursiveFollow(visited, SVR, deviceMap, true)
println()

println("PART 1: $(numberOfPaths[])")
println("PART 2: $(numberOfPaths2[])")