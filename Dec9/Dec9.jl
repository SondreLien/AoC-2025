using PolygonOps
using Luxor
using Plots
using LinearAlgebra

# set working directory
cd(@__DIR__)

# import file

InputData = read("DATA_1.txt", String)
lines = split(InputData, "\r\n")

largestX = 0
largestY = 0

redTiles = Set{NTuple{2, Int}}()
for i in eachindex(lines)
    line = lines[i]
    strcoords = split(line, ",")
    coords = (parse(Int, strcoords[1]), parse(Int, strcoords[2]))
    push!(redTiles, coords)
end

biggestRectangle = 0
biggestRectangle2 = 0

# Define perimeter
# find top left entry
startPoint = (100000, 100000)
leftBoundary = 1
upperBoundary = 1
rightBoundary = 0
lowerBoundary = 0
for entry in redTiles
    if (entry[1] <= startPoint[1] && entry[2] < startPoint[2])
        global startPoint = entry;
    end
    if (entry[1] > rightBoundary)
        global rightBoundary = entry[1]
    end
    if (entry[2] > lowerBoundary)
        global lowerBoundary = entry[2]
    end
end

println()

println("Startpoint: $startPoint, Lower boundary $lowerBoundary, Right boundary: $rightBoundary")

polygonJuncs = Vector{NTuple{2, Int}}()
push!(polygonJuncs, startPoint)
currentPoint = startPoint
currentDir = 'R'
lastMoveDir = 'L'

while true
    if length(polygonJuncs) > 1 && currentPoint == startPoint
        break
    end

    # Go right
    if currentDir == 'R'
        for i in currentPoint[1]:rightBoundary
            if i == currentPoint[1]
                continue
            end
            if (i, currentPoint[2]) in redTiles
                push!(polygonJuncs, (i, currentPoint[2]))
                global currentPoint = (i, currentPoint[2])
                global lastMoveDir = currentDir
                break;
            end 
        end
        if lastMoveDir == 'U'
            global currentDir = 'L'
        else
            global currentDir = 'D'
        end
        continue
    end
    # Go down
    if currentDir == 'D'
        for i in currentPoint[2]:lowerBoundary
            if i == currentPoint[2]
                continue
            end
            if (currentPoint[1], i) in redTiles
                push!(polygonJuncs, (currentPoint[1], i))
                global currentPoint = (currentPoint[1], i)
                global lastMoveDir = currentDir
                break;
            end
        end
        if lastMoveDir == 'R'
            global currentDir = 'U'
        else
            global currentDir = 'L'
        end
        continue
    end
    # Go left
    if currentDir == 'L'
        for i in currentPoint[1]:-1:leftBoundary
            if i == currentPoint[1]
                continue
            end
            if (i, currentPoint[2]) in redTiles
                push!(polygonJuncs, (i, currentPoint[2]))
                global currentPoint = (i, currentPoint[2])
                global lastMoveDir = currentDir
                break;
            end
        end
        if lastMoveDir == 'D'
            global currentDir = 'R'
        else
            global currentDir = 'U'
        end
        continue
    end
    # Go up
    if currentDir == 'U'
        for i in currentPoint[2]:-1:upperBoundary
            if i == currentPoint[2]
                continue
            end
            if (currentPoint[1], i) in redTiles
                push!(polygonJuncs, (currentPoint[1], i))
                global currentPoint = (currentPoint[1], i)
                global lastMoveDir = currentDir
                break;
            end
        end
        if lastMoveDir == 'L'
            global currentDir = 'D'
        else
            global currentDir = 'R'
        end
        continue
    end
end

progressCounter = 1
polygon = [(float(x), float(y)) for (x, y) in polygonJuncs]

display(polygon)
biggestRect_points = Vector{NTuple{2, float}}()
biggestRect_points2 = Vector{NTuple{2, float}}()

for entry1 in redTiles

    global progressCounter += 1

    for entry2 in redTiles
        if entry1 == entry2
            continue
        end

        dx = Int(abs(entry1[1] - entry2[1]) + 1)
        dy = Int(abs(entry1[2] - entry2[2]) + 1)

        area = dx * dy

        if area > biggestRectangle
            global biggestRectangle = area
            global biggestRect_points = [(float(entry1[1]), float(entry1[2])), (float(entry1[1]), float(entry2[2])), (float(entry2[1]), float(entry2[2])), (float(entry2[1]), float(entry1[2])), (float(entry1[1]), float(entry1[2]))]
        end

        if area > biggestRectangle2
            rectangle = [(float(entry1[1]), float(entry1[2])), (float(entry1[1]), float(entry2[2])), (float(entry2[1]), float(entry2[2])), (float(entry2[1]), float(entry1[2])), (float(entry1[1]), float(entry1[2]))]

            invalid = false;

            # Check if points are within polygon
            for point in rectangle
                if inpolygon(point, polygon) == 0
                    invalid = true
                    break
                end
            end

            if invalid
                continue
            end

            # Check if lines intersect
            for i in 1:(length(rectangle) - 1)
                rec_point1 = Luxor.Point(rectangle[i][1], rectangle[i][2])
                rec_point2 = Luxor.Point(rectangle[i + 1][1], rectangle[i + 1][2])
                rec_vector = collect([rectangle[i][1], rectangle[i][2]] .- [rectangle[i + 1][1], rectangle[i + 1][2]])

                for j in 1:(length(polygon) - 1)
                    pol_point1 = Luxor.Point(polygon[j][1], polygon[j][2])
                    pol_point2 = Luxor.Point(polygon[j + 1][1], polygon[j + 1][2])
                    pol_vector = collect([polygon[i][1], polygon[i][2]] .- [polygon[i + 1][1], polygon[i + 1][2]])
                    
                    # Only consider perpendicular vectors
                    if (dot(rec_vector, pol_vector) == 0)

                        hasIntersection, point = intersectionlines(rec_point1, rec_point2, pol_point1, pol_point2, crossingonly=true)

                        if hasIntersection && point != rec_point1 && point != rec_point2 && point != pol_point1 && point != pol_point2
                            invalid = true
                            break
                        end
                    end
                end
                if invalid
                    break
                end
            end

            if (!invalid)
                global biggestRect_points2 = rectangle
                global biggestRectangle2 = area
            end
        end
    end
end

println("Biggest area (Part 1): $biggestRectangle")
println("Biggest area (Part 2): $biggestRectangle2")

#Polygon
x_coords = [p[1] for p in polygon]
y_coords = [p[2] for p in polygon]
#Rectangle1
x_coords1 = [p[1] for p in biggestRect_points]
y_coords1 = [p[2] for p in biggestRect_points]
#Rectangle2
x_coords2 = [p[1] for p in biggestRect_points2]
y_coords2 = [p[2] for p in biggestRect_points2]

plot(x_coords, y_coords, seriestype=:shape, linecolor=:black, legend=false)
plot!(x_coords1, y_coords1, seriestype=:shape, linecolor=:green, legend=false)
plot!(x_coords2, y_coords2, seriestype=:shape, linecolor=:green, legend=false)