--====================================================
-- 👑 NGUYỄN LƯƠNG HOÀNG 8A5 👑
-- ❤️Nguyễn Lương Hoàng Hub❤️ - V6 - Phát skibidi🐍
--====================================================

local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UIS = game:GetService("UserInputService")
local Lighting = game:GetService("Lighting")
local TweenService = game:GetService("TweenService")
local Terrain = workspace:WaitForChild("Terrain")

local player = Players.LocalPlayer
local mouse = player:GetMouse()
local camera = workspace.CurrentCamera

--====================================================
-- 🚀 MÀN HÌNH LOADING (TÍCH HỢP MỚI)
--====================================================
local loadGui = Instance.new("ScreenGui", player:WaitForChild("PlayerGui"))
loadGui.Name = "LoadingScreen_NLH"
loadGui.IgnoreGuiInset = true
loadGui.ResetOnSpawn = false

local loadBg = Instance.new("Frame", loadGui)
loadBg.Size = UDim2.new(1, 0, 1, 0)
loadBg.BackgroundColor3 = Color3.fromRGB(15, 15, 20)
loadBg.BorderSizePixel = 0

-- Thanh Bar ở dưới cùng
local barBg = Instance.new("Frame", loadBg)
barBg.Size = UDim2.new(1, 0, 0, 8)
barBg.Position = UDim2.new(0, 0, 1, -8)
barBg.BackgroundColor3 = Color3.fromRGB(30, 30, 30)
barBg.BorderSizePixel = 0

local barFill = Instance.new("Frame", barBg)
barFill.Size = UDim2.new(0, 0, 1, 0)
barFill.BackgroundColor3 = Color3.fromRGB(255, 0, 0)
barFill.BorderSizePixel = 0

-- Chữ phần trăm %
local pctText = Instance.new("TextLabel", loadBg)
pctText.Size = UDim2.new(1, 0, 0, 50)
pctText.Position = UDim2.new(0, 0, 1, -60)
pctText.BackgroundTransparency = 1
pctText.Font = Enum.Font.GothamBold
pctText.TextSize = 20
pctText.TextColor3 = Color3.fromRGB(255, 255, 255)
pctText.Text = "Loading... 0%"

-- Chữ Tên VVIP (ẩn lúc đầu)
local nameText = Instance.new("TextLabel", loadBg)
nameText.Size = UDim2.new(1, 0, 1, 0)
nameText.Position = UDim2.new(0, 0, 0, 0)
nameText.BackgroundTransparency = 1
nameText.Font = Enum.Font.GothamBlack
nameText.TextSize = 45
nameText.Text = "👑 NGUYỄN LƯƠNG HOÀNG 8A5 👑"
nameText.TextTransparency = 1

-- Hiệu ứng Rainbow cho Loading
local loadingActive = true
task.spawn(function()
	local hue = 0
	while loadingActive do
		hue = hue + 0.005
		if hue >= 1 then hue = 0 end
		local currentColor = Color3.fromHSV(hue, 1, 1)
		barFill.BackgroundColor3 = currentColor
		nameText.TextColor3 = currentColor
		task.wait()
	end
end)

-- Chạy Loading từ 1% đến 100%
for i = 1, 100 do
	barFill.Size = UDim2.new(i/100, 0, 1, 0)
	pctText.Text = "Loading... " .. i .. "%"
	task.wait(0.01) -- Chỉnh tốc độ nhanh lại để test
end

-- Tắt Bar, Hiện Chữ Tên Màn Hình
task.wait(0.2)
barBg:Destroy()
pctText:Destroy()

-- Fade in chữ
TweenService:Create(nameText, TweenInfo.new(0.5), {TextTransparency = 0}):Play()
task.wait(2.5) -- Thời gian hiển thị chữ tên

-- Fade out tất cả
local fadeOutText = TweenService:Create(nameText, TweenInfo.new(1), {TextTransparency = 1})
local fadeOutBg = TweenService:Create(loadBg, TweenInfo.new(1), {BackgroundTransparency = 1})

fadeOutText:Play()
fadeOutBg:Play()
fadeOutBg.Completed:Wait() -- Đợi mờ hẳn rồi mới chạy menu

loadingActive = false
loadGui:Destroy()

--====================================================
-- BẮT ĐẦU MENU ADMIN SAU KHI LOADING XONG
--====================================================
local USER_ICON_ID = "rbxassetid://13476839304" 

-- Variables & Settings (ĐÃ THÊM KILL AURA & FPS BOOST)
local settings = {
	speed = 16,
	jump = 50,
	flySpeed = 70,
	esp = false,
	hitbox = false,
	fly = false,
	noclip = false,
	infJump = false,
	camLock = false,
	clickTp = false,
	autoTpTarget = nil,
	fullbright = false,
	optimize = false,
	killAura = false,
	killAuraRange = 15,
	fpsBoost = false
}

local function getChar()
	return player.Character or player.CharacterAdded:Wait()
end

--====================================================
-- NOTIFICATION SYSTEM
--====================================================
local notifGui = Instance.new("ScreenGui", player:WaitForChild("PlayerGui"))
notifGui.Name = "NotifV7"

local notifList = Instance.new("Frame", notifGui)
notifList.Size = UDim2.new(0, 250, 1, -50)
notifList.Position = UDim2.new(1, -260, 0, 20)
notifList.BackgroundTransparency = 1
local notifLayout = Instance.new("UIListLayout", notifList)
notifLayout.SortOrder = Enum.SortOrder.LayoutOrder
notifLayout.VerticalAlignment = Enum.VerticalAlignment.Bottom
notifLayout.Padding = UDim.new(0, 10)

local function notify(title, text)
	local frame = Instance.new("Frame", notifList)
	frame.Size = UDim2.new(1, 0, 0, 60)
	frame.BackgroundColor3 = Color3.fromRGB(30, 30, 45)
	frame.BackgroundTransparency = 1
	Instance.new("UICorner", frame).CornerRadius = UDim.new(0, 8)

	local titleLbl = Instance.new("TextLabel", frame)
	titleLbl.Size = UDim2.new(1, -10, 0, 25)
	titleLbl.Position = UDim2.new(0, 10, 0, 5)
	titleLbl.BackgroundTransparency = 1
	titleLbl.Text = title
	titleLbl.Font = Enum.Font.GothamBold
	titleLbl.TextColor3 = Color3.fromRGB(0, 255, 255)
	titleLbl.TextXAlignment = Enum.TextXAlignment.Left
	titleLbl.TextTransparency = 1

	local textLbl = Instance.new("TextLabel", frame)
	textLbl.Size = UDim2.new(1, -10, 0, 25)
	textLbl.Position = UDim2.new(0, 10, 0, 30)
	textLbl.BackgroundTransparency = 1
	textLbl.Text = text
	textLbl.Font = Enum.Font.Gotham
	textLbl.TextColor3 = Color3.fromRGB(200, 200, 200)
	textLbl.TextXAlignment = Enum.TextXAlignment.Left
	textLbl.TextTransparency = 1

	TweenService:Create(frame, TweenInfo.new(0.3), {BackgroundTransparency = 0}):Play()
	TweenService:Create(titleLbl, TweenInfo.new(0.3), {TextTransparency = 0}):Play()
	TweenService:Create(textLbl, TweenInfo.new(0.3), {TextTransparency = 0}):Play()

	task.delay(3, function()
		TweenService:Create(frame, TweenInfo.new(0.5), {BackgroundTransparency = 1}):Play()
		TweenService:Create(titleLbl, TweenInfo.new(0.5), {TextTransparency = 1}):Play()
		TweenService:Create(textLbl, TweenInfo.new(0.5), {TextTransparency = 1}):Play()
		task.wait(0.5)
		frame:Destroy()
	end)
end

--====================================================
-- FPS BOOST & TỐI ƯU HOÁ LOGIC
--====================================================
local originalLightingSettings = {
	Ambient = Lighting.Ambient,
	OutdoorAmbient = Lighting.OutdoorAmbient,
	Brightness = Lighting.Brightness,
	GlobalShadows = Lighting.GlobalShadows,
	ClockTime = Lighting.ClockTime
}
local postProcessingEffects = {} 

local function applyFullbright(state)
	if state then
		Lighting.Ambient = Color3.new(1, 1, 1)
		Lighting.OutdoorAmbient = Color3.new(1, 1, 1)
		Lighting.Brightness = 2
		Lighting.GlobalShadows = false
		Lighting.ClockTime = 14
	else
		Lighting.Ambient = originalLightingSettings.Ambient
		Lighting.OutdoorAmbient = originalLightingSettings.OutdoorAmbient
		Lighting.Brightness = originalLightingSettings.Brightness
		Lighting.GlobalShadows = originalLightingSettings.GlobalShadows
		Lighting.ClockTime = originalLightingSettings.ClockTime
	end
end

local function applyOptimization(state)
	if state then
		Lighting.GlobalShadows = false
		Lighting.Technology = Enum.Technology.Compatibility

		for _, v in pairs(Lighting:GetChildren()) do
			if v:IsA("PostEffect") or v:IsA("BloomEffect") or v:IsA("BlurEffect") or v:IsA("ColorCorrectionEffect") or v:IsA("SunRaysEffect") then
				if not postProcessingEffects[v] then postProcessingEffects[v] = v.Enabled end
				v.Enabled = false
			end
		end
	else
		Lighting.GlobalShadows = originalLightingSettings.GlobalShadows
		for effect, enabled in pairs(postProcessingEffects) do
			if effect:IsA("BasePart") or effect:IsA("PostEffect") then 
				effect.Enabled = enabled
			end
		end
		postProcessingEffects = {}
	end
end

-- DATA CACHE CHO CỰC HẠN FPS BOOST
local fpsBoostCache = {}
local function toggleExtremeFPSBoost(state)
	if state then
		for _, v in pairs(workspace:GetDescendants()) do
			if v:IsA("BasePart") then
				fpsBoostCache[v] = {Color = v.Color, Material = v.Material}
				v.Material = Enum.Material.SmoothPlastic
				v.Color = Color3.fromRGB(150, 150, 150) -- Màu xám
			elseif v:IsA("Texture") or v:IsA("Decal") then
				fpsBoostCache[v] = {Transparency = v.Transparency}
				v.Transparency = 1
			elseif v:IsA("ParticleEmitter") or v:IsA("Trail") or v:IsA("Beam") or v:IsA("Fire") or v:IsA("Smoke") or v:IsA("Sparkles") then
				fpsBoostCache[v] = {Enabled = v.Enabled}
				v.Enabled = false
			end
		end
	else
		for v, data in pairs(fpsBoostCache) do
			if v.Parent then
				if v:IsA("BasePart") then
					v.Color = data.Color
					v.Material = data.Material
				elseif v:IsA("Texture") or v:IsA("Decal") then
					v.Transparency = data.Transparency
				elseif v:IsA("ParticleEmitter") or v:IsA("Trail") or v:IsA("Beam") or v:IsA("Fire") or v:IsA("Smoke") or v:IsA("Sparkles") then
					v.Enabled = data.Enabled
				end
			end
		end
		fpsBoostCache = {}
	end
end

--====================================================
-- MAIN GUI SETUP
--====================================================
local gui = Instance.new("ScreenGui", player.PlayerGui)
gui.Name = "AdminV7"
gui.ResetOnSpawn = false

local frame = Instance.new("Frame", gui)
frame.Size = UDim2.new(0, 650, 0, 450)
frame.Position = UDim2.new(0.5, -325, 0.5, -225)
frame.BackgroundColor3 = Color3.fromRGB(20, 20, 30)
frame.BorderSizePixel = 0
frame.ClipsDescendants = true
Instance.new("UICorner", frame).CornerRadius = UDim.new(0, 10)

local rgbLine = Instance.new("Frame", frame)
rgbLine.Size = UDim2.new(1, 0, 0, 3)
rgbLine.BackgroundColor3 = Color3.fromRGB(0, 255, 255)
rgbLine.BorderSizePixel = 0

task.spawn(function()
	local hue = 0
	while task.wait() do
		hue = hue + 0.005
		if hue >= 1 then hue = 0 end
		rgbLine.BackgroundColor3 = Color3.fromHSV(hue, 1, 1)
	end
end)

local function makeDraggable(obj)
	local dragging, dragInput, dragStart, startPos
	obj.InputBegan:Connect(function(input)
		if input.UserInputType == Enum.UserInputType.MouseButton1 or input.UserInputType == Enum.UserInputType.Touch then
			dragging = true
			dragStart = input.Position
			startPos = obj.Position
			input.Changed:Connect(function()
				if input.UserInputState == Enum.UserInputState.End then dragging = false end
			end)
		end
	end)
	obj.InputChanged:Connect(function(input)
		if input.UserInputType == Enum.UserInputType.MouseMovement or input.UserInputType == Enum.UserInputType.Touch then dragInput = input end
	end)
	UIS.InputChanged:Connect(function(input)
		if input == dragInput and dragging then
			local delta = input.Position - dragStart
			obj.Position = UDim2.new(startPos.X.Scale, startPos.X.Offset + delta.X, startPos.Y.Scale, startPos.Y.Offset + delta.Y)
		end
	end)
end
makeDraggable(frame)

local maximized = true
local mini = Instance.new("ImageButton", gui)
mini.Name = "UserMinimizeBtn"
mini.Size = UDim2.new(0, 50, 0, 50)
mini.Position = UDim2.new(0, 20, 0, 20)
mini.Image = USER_ICON_ID 
mini.BackgroundColor3 = Color3.fromRGB(30, 30, 45)
mini.BackgroundTransparency = 0.5
Instance.new("UICorner", mini).CornerRadius = UDim.new(0, 25) 

local titleLabel = Instance.new("TextLabel", frame)
titleLabel.Name = "TitleHeader"
titleLabel.Size = UDim2.new(1, -60, 0, 40)
titleLabel.Position = UDim2.new(0, 10, 0, 5)
titleLabel.Text = "👑 ADMIN EXPERIENCE - V4.0 ADVANCED"
titleLabel.Font = Enum.Font.GothamBold
titleLabel.TextColor3 = Color3.fromRGB(255, 255, 255)
titleLabel.BackgroundTransparency = 1
titleLabel.TextXAlignment = Enum.TextXAlignment.Left

mini.MouseButton1Click:Connect(function()
	maximized = not maximized
	if maximized then
		TweenService:Create(frame, TweenInfo.new(0.4, Enum.EasingStyle.Back, Enum.EasingDirection.Out), {Size = UDim2.new(0, 650, 0, 450)}):Play()
		mini.BackgroundTransparency = 0.5 
	else
		TweenService:Create(frame, TweenInfo.new(0.4, Enum.EasingStyle.Back, Enum.EasingDirection.In), {Size = UDim2.new(0, 650, 0, 0)}):Play()
		mini.BackgroundTransparency = 0 
	end
end)

--====================================================
-- UI COMPONENTS
--====================================================
local tabContainer = Instance.new("Frame", frame)
tabContainer.Size = UDim2.new(1, 0, 0, 50)
tabContainer.Position = UDim2.new(0, 0, 0, 50) 
tabContainer.BackgroundTransparency = 1

local tabListLayout = Instance.new("UIListLayout", tabContainer)
tabListLayout.FillDirection = Enum.FillDirection.Horizontal
tabListLayout.Padding = UDim.new(0, 5)

local contentContainer = Instance.new("Frame", frame)
contentContainer.Size = UDim2.new(1, 0, 1, -100) 
contentContainer.Position = UDim2.new(0, 0, 0, 100) 
contentContainer.BackgroundTransparency = 1

local tabs = {}
local function createTab(name)
	local btn = Instance.new("TextButton", tabContainer)
	btn.Size = UDim2.new(0, 100, 1, 0)
	btn.Text = name
	btn.Font = Enum.Font.GothamSemibold
	btn.TextColor3 = Color3.fromRGB(150, 150, 150)
	btn.BackgroundTransparency = 1

	local page = Instance.new("ScrollingFrame", contentContainer)
	page.Size = UDim2.new(1, -20, 1, -20)
	page.Position = UDim2.new(0, 10, 0, 10)
	page.BackgroundTransparency = 1
	page.ScrollBarThickness = 4
	page.Visible = false

	local listLayout = Instance.new("UIListLayout", page)
	listLayout.Padding = UDim.new(0, 8)

	btn.MouseButton1Click:Connect(function()
		for _, v in pairs(tabs) do
			v.page.Visible = false
			TweenService:Create(v.btn, TweenInfo.new(0.2), {TextColor3 = Color3.fromRGB(150, 150, 150)}):Play()
		end
		page.Visible = true
		TweenService:Create(btn, TweenInfo.new(0.2), {TextColor3 = Color3.fromRGB(255, 255, 255)}):Play()
	end)

	tabs[name] = {page = page, btn = btn}
	return page
end

local function createButton(parent, text, func)
	local b = Instance.new("TextButton", parent)
	b.Size = UDim2.new(1, -10, 0, 40)
	b.Text = text
	b.Font = Enum.Font.Gotham
	b.TextColor3 = Color3.fromRGB(255, 255, 255)
	b.BackgroundColor3 = Color3.fromRGB(35, 35, 50)
	Instance.new("UICorner", b).CornerRadius = UDim.new(0, 6)
	b.MouseButton1Click:Connect(func)
	return b
end

local function createTextBoxSection(parent, labelText, defaultValue, placeholderText, func)
	local frame = Instance.new("Frame", parent)
	frame.Size = UDim2.new(1, -10, 0, 60)
	frame.BackgroundColor3 = Color3.fromRGB(35, 35, 50)
	frame.BorderSizePixel = 0
	Instance.new("UICorner", frame).CornerRadius = UDim.new(0, 6)

	local label = Instance.new("TextLabel", frame)
	label.Size = UDim2.new(1, -10, 0, 20)
	label.Position = UDim2.new(0, 5, 0, 5)
	label.Text = labelText
	label.Font = Enum.Font.Gotham
	label.TextColor3 = Color3.fromRGB(150, 150, 150)
	label.BackgroundTransparency = 1
	label.TextXAlignment = Enum.TextXAlignment.Left

	local textBox = Instance.new("TextBox", frame)
	textBox.Size = UDim2.new(1, -20, 0, 30)
	textBox.Position = UDim2.new(0, 10, 0, 25)
	textBox.Text = tostring(defaultValue)
	textBox.PlaceholderText = placeholderText
	textBox.Font = Enum.Font.Gotham
	textBox.TextColor3 = Color3.fromRGB(255, 255, 255)
	textBox.BackgroundColor3 = Color3.fromRGB(20, 20, 30)
	Instance.new("UICorner", textBox).CornerRadius = UDim.new(0, 4)

	textBox.FocusLost:Connect(function(enterPressed)
		local value = tonumber(textBox.Text)
		if value then
			func(value)
			notify(labelText, "Đã đặt thành: " .. value)
		else
			notify(labelText .. " LỖI", "Giá trị nhập không hợp lệ (nhập số)")
			textBox.Text = tostring(defaultValue)
		end
	end)
	return frame, textBox
end

-- Tabs Initialization
local mainTab = createTab("Main")
local combatTab = createTab("Combat")
local tpTab = createTab("Players")
local autoTab = createTab("Auto TP")
local espTab = createTab("Visuals")
local miscTab = createTab("Misc") 

tabs["Main"].page.Visible = true
tabs["Main"].btn.TextColor3 = Color3.fromRGB(255, 255, 255)

-- MISC TAB
createButton(miscTab, "Toggle Full Bright", function()
	settings.fullbright = not settings.fullbright
	applyFullbright(settings.fullbright)
	notify("Full Bright", settings.fullbright and "Đã BẬT (Loại bỏ bóng)" or "Đã TẮT")
end)

createButton(miscTab, "Toggle Game Optimization", function()
	settings.optimize = not settings.optimize
	applyOptimization(settings.optimize)
	notify("Tối ưu hóa Game", settings.optimize and "Đã BẬT (Medium: Tắt hiệu ứng post-process)" or "Đã TẮT")
end)

-- [TÍNH NĂNG MỚI: FPS BOOST CỰC HẠN]
createButton(miscTab, "Toggle FPS Boost (Xám map + Tắt Animation)", function()
	settings.fpsBoost = not settings.fpsBoost
	toggleExtremeFPSBoost(settings.fpsBoost)
	notify("FPS Boost", settings.fpsBoost and "Đã BẬT (Đã biến khối thành xám, xóa Animation)" or "Đã TẮT (Khôi phục đồ họa)")
end)

createTextBoxSection(mainTab, "Set WalkSpeed", settings.speed, "Nhập tốc độ chạy...", function(value)
	settings.speed = value
	local hum = getChar():FindFirstChild("Humanoid")
	if hum then hum.WalkSpeed = value end
end)

createTextBoxSection(mainTab, "Set JumpPower", settings.jump, "Nhập sức nhảy...", function(value)
	settings.jump = value
	local hum = getChar():FindFirstChild("Humanoid")
	if hum then hum.JumpPower = value end
end)

--====================================================
-- PHẦN FLY, NOCLIP, TP, ESP...
--====================================================
local miniFlyFrame = Instance.new("Frame", gui)
miniFlyFrame.Size = UDim2.new(0, 120, 0, 40)
miniFlyFrame.Position = UDim2.new(0.5, 340, 0.5, -20)
miniFlyFrame.BackgroundColor3 = Color3.fromRGB(30, 30, 30)
miniFlyFrame.BorderSizePixel = 0
miniFlyFrame.Active = true
miniFlyFrame.Visible = false
Instance.new("UICorner", miniFlyFrame).CornerRadius = UDim.new(0, 8)

local miniToggleBtn = Instance.new("TextButton", miniFlyFrame)
miniToggleBtn.Size = UDim2.new(0.6, 0, 1, 0)
miniToggleBtn.BackgroundTransparency = 1
miniToggleBtn.Text = "Fly: ON"
miniToggleBtn.TextColor3 = Color3.fromRGB(0, 255, 127)
miniToggleBtn.Font = Enum.Font.GothamBold
miniToggleBtn.TextSize = 14

local subFlyFrame = Instance.new("Frame", miniFlyFrame)
subFlyFrame.Size = UDim2.new(0.4, -5, 0, 30)
subFlyFrame.Position = UDim2.new(0.6, 0, 0, 5)
subFlyFrame.BackgroundColor3 = Color3.fromRGB(50, 50, 50)
subFlyFrame.BackgroundTransparency = 0.2
Instance.new("UICorner", subFlyFrame)

-- [TÍNH NĂNG MỚI: TEXTBOX CHỈNH TỐC ĐỘ BAY]
local speedInput = Instance.new("TextBox", subFlyFrame)
speedInput.Size = UDim2.new(1, 0, 1, 0)
speedInput.BackgroundTransparency = 1
speedInput.Text = tostring(settings.flySpeed)
speedInput.TextColor3 = Color3.fromRGB(0, 255, 255)
speedInput.Font = Enum.Font.Gotham
speedInput.TextSize = 14
speedInput.ClearTextOnFocus = false

speedInput.FocusLost:Connect(function()
	local val = tonumber(speedInput.Text)
	if val then
		settings.flySpeed = val
		notify("Fly Speed", "Tốc độ bay đã chuyển thành: " .. val)
	else
		speedInput.Text = tostring(settings.flySpeed)
	end
end)

makeDraggable(miniFlyFrame)

local bodyVelocity, bodyGyro

local function stopFly()
	settings.fly = false
	miniFlyFrame.Visible = false
	RunService:UnbindFromRenderStep("FlyStep")
	if bodyVelocity then bodyVelocity:Destroy() end
	if bodyGyro then bodyGyro:Destroy() end
	local char = getChar()
	if char and char:FindFirstChild("Humanoid") then
		char.Humanoid.PlatformStand = false
	end
	notify("Fly", "Đã TẮT Fly")
end

local function startFly()
	local char = getChar()
	local hrp = char:WaitForChild("HumanoidRootPart")
	local hum = char:WaitForChild("Humanoid")

	settings.fly = true
	miniFlyFrame.Visible = true
	hum.PlatformStand = true 

	bodyVelocity = Instance.new("BodyVelocity", hrp)
	bodyVelocity.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
	bodyVelocity.Velocity = Vector3.zero

	bodyGyro = Instance.new("BodyGyro", hrp)
	bodyGyro.MaxTorque = Vector3.new(math.huge, math.huge, math.huge)
	bodyGyro.CFrame = hrp.CFrame

	RunService:BindToRenderStep("FlyStep", Enum.RenderPriority.Camera.Value, function()
		if not settings.fly or not hrp then return end
		local moveDir = hum.MoveDirection 
		if moveDir.Magnitude > 0 then
			local relativeDir = camera.CFrame:VectorToObjectSpace(moveDir)
			local finalDir = (camera.CFrame.LookVector * -relativeDir.Z) + (camera.CFrame.RightVector * relativeDir.X)
			bodyVelocity.Velocity = finalDir * settings.flySpeed
		else
			bodyVelocity.Velocity = Vector3.zero
		end
		bodyGyro.CFrame = camera.CFrame
	end)
	notify("Fly", "Đã BẬT Fly (Hỗ trợ Joystick/WASD)")
end

miniToggleBtn.MouseButton1Click:Connect(stopFly)

createButton(mainTab, "Toggle Fly 3D (Mobile)", function()
	if settings.fly then stopFly() else startFly() end
end)

createButton(mainTab, "Toggle Noclip", function()
	settings.noclip = not settings.noclip
	notify("Noclip", settings.noclip and "Đã BẬT đi xuyên tường" or "Đã TẮT")
end)

createButton(mainTab, "Ctrl + Click TP", function()
	settings.clickTp = not settings.clickTp
	notify("Click TP", settings.clickTp and "Giữ Ctrl + Click trái để TP" or "Đã TẮT Click TP")
end)

mouse.Button1Down:Connect(function()
	if settings.clickTp and UIS:IsKeyDown(Enum.KeyCode.LeftControl) then
		local root = getChar():FindFirstChild("HumanoidRootPart")
		if root and mouse.Hit then
			root.CFrame = CFrame.new(mouse.Hit.Position + Vector3.new(0, 3, 0))
		end
	end
end)

--====================================================
-- COMBAT TAB (CAMLOCK & KILL AURA)
--====================================================
createButton(combatTab, "Toggle CamLock (Aimbot)", function()
	settings.camLock = not settings.camLock
	notify("CamLock", settings.camLock and "Khóa góc nhìn: BẬT" or "Đã TẮT")
end)

-- [TÍNH NĂNG MỚI: KILL AURA + TEXT BOX PHẠM VI]
createButton(combatTab, "Toggle Kill Aura", function()
	settings.killAura = not settings.killAura
	notify("Kill Aura", settings.killAura and ("Đã BẬT (Phạm vi: " .. settings.killAuraRange .. ")") or "Đã TẮT")
end)

createTextBoxSection(combatTab, "Chỉnh phạm vi Kill Aura", settings.killAuraRange, "Nhập phạm vi (VD: 15)...", function(val)
	settings.killAuraRange = val
end)

local function getClosestPlayer()
	local closestDist = math.huge
	local target = nil
	for _, p in pairs(Players:GetPlayers()) do
		if p ~= player and p.Character and p.Character:FindFirstChild("Head") then
			local pos, onScreen = camera:WorldToViewportPoint(p.Character.Head.Position)
			if onScreen then
				local dist = (Vector2.new(pos.X, pos.Y) - Vector2.new(mouse.X, mouse.Y)).Magnitude
				if dist < closestDist then closestDist = dist target = p end
			end
		end
	end
	return target
end

--====================================================
-- CÁC VÒNG LẶP HỆ THỐNG XỬ LÝ (RUNSERVICE)
--====================================================
RunService.Stepped:Connect(function()
	-- Xử lý Noclip
	if settings.noclip then
		local char = player.Character
		if char then
			for _, v in pairs(char:GetDescendants()) do
				if v:IsA("BasePart") then v.CanCollide = false end
			end
		end
	end
	
	-- Xử lý đóng băng chuyển động (Animation) cho FPS Boost
	if settings.fpsBoost then
		for _, p in pairs(Players:GetPlayers()) do
			if p.Character then
				local hum = p.Character:FindFirstChild("Humanoid")
				if hum then
					for _, track in pairs(hum:GetPlayingAnimationTracks()) do
						track:Stop()
					end
				end
			end
		end
	end
end)

RunService.RenderStepped:Connect(function()
	if settings.camLock then
		local target = getClosestPlayer()
		if target and target.Character and target.Character:FindFirstChild("Head") then
			camera.CFrame = CFrame.new(camera.CFrame.Position, target.Character.Head.Position)
		end
	end
end)

RunService.Heartbeat:Connect(function()
	-- Xử lý Auto TP
	if settings.autoTpTarget and settings.autoTpTarget.Character then
		local t = settings.autoTpTarget.Character:FindFirstChild("HumanoidRootPart")
		local m = getChar():FindFirstChild("HumanoidRootPart")
		if t and m then m.CFrame = t.CFrame * CFrame.new(0, 0, -3) end
	end
	
	-- Xử lý Hitbox
	if settings.hitbox then
		for _, plr in pairs(Players:GetPlayers()) do
			if plr ~= player and plr.Character then
				local r = plr.Character:FindFirstChild("HumanoidRootPart")
				if r then r.Size = Vector3.new(10, 10, 10) r.Transparency = 0.7 r.CanCollide = false end
			end
		end
	end

	-- Xử lý Kill Aura
	if settings.killAura then
		local char = player.Character
		if char then
			local hrp = char:FindFirstChild("HumanoidRootPart")
			local tool = char:FindFirstChildOfClass("Tool")
			if hrp and tool and tool:FindFirstChild("Handle") then
				for _, p in pairs(Players:GetPlayers()) do
					if p ~= player and p.Character and p.Character:FindFirstChild("HumanoidRootPart") and p.Character:FindFirstChild("Humanoid") and p.Character.Humanoid.Health > 0 then
						local dist = (p.Character.HumanoidRootPart.Position - hrp.Position).Magnitude
						if dist <= settings.killAuraRange then
							-- Tự động đánh (Dùng firetouchinterest cực chuẩn xác, backup là Tool:Activate)
							if firetouchinterest then
								firetouchinterest(tool.Handle, p.Character.HumanoidRootPart, 0)
								firetouchinterest(tool.Handle, p.Character.HumanoidRootPart, 1)
							else
								tool:Activate()
							end
						end
					end
				end
			end
		end
	end
end)

--====================================================
-- AUTO TP & ESP DANH SÁCH NGƯỜI CHƠI
--====================================================
local function updatePlayerLists()
	for _, v in pairs(tpTab:GetChildren()) do if v:IsA("TextButton") then v:Destroy() end end
	for _, v in pairs(autoTab:GetChildren()) do if v:IsA("TextButton") then v:Destroy() end end
	createButton(autoTab, "🛑 Dừng Auto TP", function() settings.autoTpTarget = nil notify("Auto TP", "Đã dừng") end)
	for _, plr in pairs(Players:GetPlayers()) do
		if plr ~= player then
			createButton(tpTab, "TP to: " .. plr.Name, function()
				if plr.Character and plr.Character:FindFirstChild("HumanoidRootPart") then
					getChar().HumanoidRootPart.CFrame = plr.Character.HumanoidRootPart.CFrame * CFrame.new(0, 0, -3)
				end
			end)
			createButton(autoTab, "Auto TP: " .. plr.Name, function() settings.autoTpTarget = plr end)
		end
	end
end
Players.PlayerAdded:Connect(updatePlayerLists)
Players.PlayerRemoving:Connect(updatePlayerLists)
updatePlayerLists()

createButton(espTab, "Toggle ESP", function()
	settings.esp = not settings.esp
	for _, plr in pairs(Players:GetPlayers()) do
		if plr ~= player and plr.Character then
			local h = plr.Character:FindFirstChild("ESPHighlight")
			if settings.esp then
				if not h then h = Instance.new("Highlight", plr.Character) h.Name = "ESPHighlight" end
			elseif h then h:Destroy() end
		end
	end
end)

createButton(espTab, "Toggle Hitbox (10x10)", function()
	settings.hitbox = not settings.hitbox
end) 
