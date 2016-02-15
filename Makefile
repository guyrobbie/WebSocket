.PHONY: clean All

All:
	@echo "----------Building project:[ WebSocket - Debug ]----------"
	@"$(MAKE)" -f  "WebSocket.mk"
clean:
	@echo "----------Cleaning project:[ WebSocket - Debug ]----------"
	@"$(MAKE)" -f  "WebSocket.mk" clean
