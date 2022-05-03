PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//527081/843695/2.49/3/2/Zener Diode

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r105_60"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.6) (shapeHeight 1.05))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "SOT95P230X110-3N" (originalName "SOT95P230X110-3N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r105_60) (pt -1.1, 0.95) (rotation 90))
			(pad (padNum 2) (padStyleRef r105_60) (pt -1.1, -0.95) (rotation 90))
			(pad (padNum 3) (padStyleRef r105_60) (pt 1.1, 0) (rotation 90))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.875 1.75) (pt 1.875 1.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.875 1.75) (pt 1.875 -1.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.875 -1.75) (pt -1.875 -1.75) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.875 -1.75) (pt -1.875 1.75) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 1.45) (pt 0.65 1.45) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.65 1.45) (pt 0.65 -1.45) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 0.65 -1.45) (pt -0.65 -1.45) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 -1.45) (pt -0.65 1.45) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -0.65 0.5) (pt 0.3 1.45) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.225 1.45) (pt 0.225 1.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.225 1.45) (pt 0.225 -1.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0.225 -1.45) (pt -0.225 -1.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -0.225 -1.45) (pt -0.225 1.45) (width 0.2))
		)
		(layerContents (layerNumRef 18)
			(line (pt -1.625 1.5) (pt -0.575 1.5) (width 0.2))
		)
	)
	(symbolDef "PESD2CAN_215" (originalName "PESD2CAN_215")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -25 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 0 mils -100 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 230 mils -125 mils) (rotation 0]) (justify "Left") (textStyleRef "Normal"))
		))
		(pin (pinNum 3) (pt 1900 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName true)) (pinName (text (pt 1670 mils -25 mils) (rotation 0]) (justify "Right") (textStyleRef "Normal"))
		))
		(line (pt 200 mils 100 mils) (pt 1700 mils 100 mils) (width 6 mils))
		(line (pt 1700 mils 100 mils) (pt 1700 mils -200 mils) (width 6 mils))
		(line (pt 1700 mils -200 mils) (pt 200 mils -200 mils) (width 6 mils))
		(line (pt 200 mils -200 mils) (pt 200 mils 100 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 1750 mils 300 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 1750 mils 200 mils) (justify Left) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "PESD2CAN,215" (originalName "PESD2CAN,215") (compHeader (numPins 3) (numParts 1) (refDesPrefix Z)
		)
		(compPin "1" (pinName "CATHODE 1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "CATHODE 2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "3" (pinName "COMMON CATHODE") (partNum 1) (symPinNum 3) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "PESD2CAN_215"))
		(attachedPattern (patternNum 1) (patternName "SOT95P230X110-3N")
			(numPads 3)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
				(padNum 3) (compPinRef "3")
			)
		)
		(attr "Manufacturer_Name" "Nexperia")
		(attr "Manufacturer_Part_Number" "PESD2CAN,215")
		(attr "Mouser Part Number" "771-PESD2CAN-T/R")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Nexperia/PESD2CAN215?qs=LOCUfHb8d9sqg7TaLUP2JQ%3D%3D")
		(attr "Arrow Part Number" "PESD2CAN,215")
		(attr "Arrow Price/Stock" "https://www.arrow.com/en/products/pesd2can215/nexperia?region=nac")
		(attr "Description" "NXP PESD2CAN,215 Dual Bi-Directional ESD Protection Diode, 230W peak, 3-Pin SOT23 (TO-236AB)")
		(attr "<Hyperlink>" "https://datasheet.datasheetarchive.com/originals/distributors/Datasheets_SAMA/5df5edafdc67e6ae251d12d61f18e7bd.pdf")
		(attr "<Component Height>" "1.1")
		(attr "<STEP Filename>" "PESD2CAN,215.stp")
		(attr "<STEP Offsets>" "X=-2.11;Y=-1.33;Z=-1.16")
		(attr "<STEP Rotation>" "X=90;Y=0;Z=90")
	)

)
