--// SERVICES
local Players = game:GetService("Players")
local player = Players.LocalPlayer

--// ANTI RESET GUI
local old = player.PlayerGui:FindFirstChild("MiniTPGui")
if old then old:Destroy() end

local screenGui = Instance.new("ScreenGui")
screenGui.Name = "MiniTPGui"
screenGui.ResetOnSpawn = false
screenGui.Parent = player:WaitForChild("PlayerGui")

--// VARIABLES
local savedPosition = nil
local multiPositions = {}

--// FRAME
local frame = Instance.new("Frame", screenGui)
frame.Size = UDim2.new(0, 170, 0, 170)
frame.Position = UDim2.new(0.5, -85, 0.5, -85)
frame.BackgroundColor3 = Color3.fromRGB(25,25,25)
frame.Active = true
frame.Draggable = true

--// TITLE
local title = Instance.new("TextLabel", frame)
title.Size = UDim2.new(1, 0, 0, 25)
title.Position = UDim2.new(0, 0, 0, 0)
title.Text = "🔄N.l.Hoàng🔄"
title.BackgroundColor3 = Color3.fromRGB(40,40,40)
title.TextColor3 = Color3.new(1,1,1)
title.TextScaled = true

--// BUTTON FUNCTION
local function createButton(text, color, posY)
    local btn = Instance.new("TextButton", frame)
    btn.Size = UDim2.new(0, 150, 0, 28)
    btn.Position = UDim2.new(0, 10, 0, posY)
    btn.Text = text
    btn.BackgroundColor3 = color
    btn.TextColor3 = Color3.new(1,1,1)
    btn.TextScaled = true
    return btn
end

--// BUTTONS
local saveBtn = createButton("SAVE (1)", Color3.fromRGB(0,255,0), 30)
local multiBtn = createButton("SAVE MULTI", Color3.fromRGB(0,150,255), 65)
local tpBtn = createButton("TP", Color3.fromRGB(255,0,0), 100)
local resetBtn = createButton("RESET", Color3.fromRGB(255,200,0), 135)

--// SAVE SINGLE
saveBtn.MouseButton1Click:Connect(function()
    local char = player.Character
    if char and char:FindFirstChild("HumanoidRootPart") then
        savedPosition = char.HumanoidRootPart.CFrame
        print("Đã lưu vị trí đơn")
    end
end)

--// SAVE MULTI
multiBtn.MouseButton1Click:Connect(function()
    local char = player.Character
    if char and char:FindFirstChild("HumanoidRootPart") then
        table.insert(multiPositions, char.HumanoidRootPart.CFrame)
        print("Đã lưu vị trí thứ: "..#multiPositions)
    end
end)

--// RESET (XOÁ TỌA ĐỘ)
resetBtn.MouseButton1Click:Connect(function()
    savedPosition = nil
    multiPositions = {}
    print("Đã xoá toàn bộ tọa độ")
end)

--// TELEPORT
tpBtn.MouseButton1Click:Connect(function()
    local char = player.Character
    if not (char and char:FindFirstChild("HumanoidRootPart")) then return end

    if #multiPositions > 0 then
        for i, pos in ipairs(multiPositions) do
            char.HumanoidRootPart.CFrame = pos
            task.wait(1)
        end
    elseif savedPosition then
        char.HumanoidRootPart.CFrame = savedPosition
    end
end)
