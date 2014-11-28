function [traces, rawF, roiList, roiGroup, traceNeuropil] = ...
    extractROIsBin(obj,roiGroups,sliceNum,channelNum)
% Function for extracting ROIs from movies using grouping assigned by
% selectROIs. This function uses a memorymapped binary file of the entire
% movie, as output by indexMovie. See extractROIsTIFF to extract ROIs
% from tiff files instead
%
% [traces,rawF,roiList] = extractROIs(obj,roiGroups,sliceNum,channelNum)
%
% roiGroups is a scalar or vector of desired groupings to extract ROIs for, defaults to all grouping (1:9)
% traces - matrix of n_cells x n_frames fluorescence values, using neuropil correction for ROIs with a matched neuropil ROI
% rawF - matrix of same size as traces, but without using neuropil correction
% roiList - vector of ROI numbers corresponding to extracted ROIs
% roiGroup - vector of ROI groupings for each returned trace.


%% Input Handling
if ~exist('sliceNum','var') || isempty(sliceNum)
    sliceNum = 1;
end
if ~exist('channelNum','var') || isempty(channelNum)
    channelNum = 1;
end
if ~exist('roiGroups','var') || isempty(roiGroups)
    roiGroups = 1:9;
end

%% ROI Extraction

%Find relevant ROIs
roiGroup = obj.roiInfo.slice(sliceNum).grouping;
roiList = find(ismember(roiGroup,roiGroups));
roiGroup = roiGroup(roiList);
nRois = numel(roiList);

%Memory Map Movie
movSizes = cat(1, obj.derivedData.size);
h = movSizes(1, 1);
w = movSizes(1, 2);
nFramesTotal = sum(movSizes(:, 3));

movMap = memmapfile(obj.indexedMovie.slice(sliceNum).channel(channelNum).fileName,...
    'Format', {'int16', [nFramesTotal, h*w], 'mov'});
mov = movMap.Data.mov;

%Loop over each ROI,
traces = nan(nRois, nFramesTotal);
rawF = nan(nRois, nFramesTotal);
traceNeuropil = nan(nRois, nFramesTotal);

for nROI = 1:nRois
    fprintf('Extracting ROI %03.0f of %03.0f\n',nROI,length(roiList));
    
    thisRoi = obj.roiInfo.slice(sliceNum).roi(roiList(nROI));
    
    indCell = obj.mat2binInd(thisRoi.indBody);
    traceCell = mean(mov(:, indCell), 2)';
    rawF(nROI,:) = traceCell;
    
    
    if isfield(thisRoi,'indNeuropil') && ~isempty(thisRoi.indNeuropil)
        subCoef = thisRoi.subCoef;
        indNeuropil = obj.mat2binInd(thisRoi.indNeuropil);
        traceNeuropil(nROI,:) = mean(mov(:, indNeuropil), 2)';
        traces(nROI,:) = traceCell - traceNeuropil(nROI,:)*subCoef;
    else
        traces(nROI,:) = rawF(nROI,:);
    end
end

clear mov